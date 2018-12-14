# What is library?
library 클래스를 선언하면 resource.dat 파일과 input.dat 파일을 읽어 ouput.dat 파일을 생성한다.

# Build library
* It is simple. just type ```make```
```
% make
% ./library
% diff output.dat <original_output_file_name>.dat
```
# Class description
* library
    * vector< book* > B : book 클래스 포인터 벡터 변수터
    * vector< magazine* > M : magazine 클래스 포인터 벡터 변수터
    * vector< e_book* > E : e_book 클래스 포인터 벡터 변수터
    * vector< undergraduate* > U : undergraduate 포인터 벡터 변수
    * vector< Study_room* > srooms : Study_room 포인터 벡터 변수
    * vector< Study_room* > seats : Seat 포인터 벡터 변수

    * void resource_data(); : resource.dat 파일을 읽어 book 벡터에 push 하는 함수
    * string check(int cnt, int date, string r_type, string r_name, string op, string m_type, string m_name); : input.dat 파일을 읽어 한줄(op 1개) 에 대한 return code를 판단 후 output.dat에 적을 string을 리턴해주고 벡터들에 수정이 필요한 경우 인자들을 Update()함수로 넘겨준다.
    * string check2(int cnt, string s_dateS, string s_type, int s_num, string s_op, string sm_type, string sm_name, int sm_num, int s_time, int hour); : space.dat 파일을 읽어 한줄(op 1개) 에 대한 return code를 판단 후 output.dat에 적을 string을 리턴해주고 Study_room, Seat 벡터에 수정이 필요한 경우에는 setter를 이용하여 수정해준다. (int hour:인풋 요청 날짜 string(2019/11/12/06) 에서 시간(6)추출)
    * void Update(int date, string m_type, string m_name, string r_type, string r_name, int op); : check()함수에서 받은 정보를 가지고 book, undergraduate 벡터를 수정하는 함수
    * bool is_registered(string name, string type); : 인자로 받는 이름이 도서관 book 벡터에 등록이 되어있는지 확인하는 함수
    * int DtoInt(string date); : yy/mm/dd 형식의 string 날짜를 int형으로 변환해주는 함수
    * string DtoString(int date); : int형의 날짜를 yy/mm/dd 형식의 string 형식으로 변환해주는 함수
    * string DtoHour(int date); : string형의 날짜(yyyy/mm/dd/hh)에서 시간(hh)를 int형으로 반환해주는 함수
    * void result(); : check, check2 함수에서 받은 string을 ouput.dat 파일에 write해주는 함수
    * void refresh(string date); : 인풋이 들어올때마다 날짜가 지났는지, 좌석 대출 기간이 지났는지 판단하여 Studyroom과 Seat를 초기화해주는 함수
    * string get_type(string name); : 멤버 이름을 입력 받으면 멤버 타입을 반환해주는 함수
    * string HtoString(int hour); : Int형식의 시간(9)을 String 형식(09)으로 변환해주는 함수
    * bool NumInString(string str); : string에 숫자가 포함되어있는지 확인하는 함수 (포함되어 있으면 true 반환, 아닐시 false 반환)

* member(undergraduate)
    * string _name : 멤버 이름
	* map< string, int > _borrow : 멤버가 빌린 resource를 resource name을 키로 가지고 빌린 날짜를 value로 가지는 map 구조로 저장
	* int _restrict_date : 도서관 이용이 언제까지 제한되는지 날짜를 저장 (제한되지 않았을 시 0)

    * 그 외 getter, setter 함수들

* resource(book)
	* string _name : resource 이름
	* string _who_borrow : 빌린 member의 이름(없을시 "")
	* int _borrow_date : 빌린 날짜(없을시 0)

    * 그 외 getter, setter 함수들

* space
	* char state : 좌석의 상태 (U:use, A:away, N:notuse)
	* string who_borrow : 빌린 member의 이름(없을시 "")
	* int when_return : 반납 시간(없을시 0)
    * 그 외 getter, setter 함수들

    * Study_room Class
        * int room_num : 스터디룸 방번호 (library 생성자에서 번호부여)
        * int how_many : 스터디룸 이용 인원(없을시 0)
        * 그 외 getter, setter 함수들
        
    * Seat Class
        * int floor : 좌석 층수 (library 생성자에서 부여)
        * int seat_num : 좌석 번호(library 생성자에서 부여)
        * int when_come : 자리비움 시 돌아와야하는 제한 시간(+1시간)
        * 그 외 getter, setter 함수들


