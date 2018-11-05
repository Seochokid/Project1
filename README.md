# What is library?
library 클래스를 선언하면 resource.dat 파일과 input.dat 파일을 읽어 ouput.dat 파일을 생성한다.

# Build library
* It is simple. just type ```make```
```
% make
% diff output.dat <original_output_file_name>.dat
```
# Class description
* library
    * vector<book> B : book 클래스 벡터 변수
    * vector<undergraduate> U : undergraduate 벡터 변수

    * void resource_data(); : resource.dat 파일을 읽어 book 벡터에 push 하는 함수
    * string check(int cnt, int date, string r_type, string r_name, string op, string m_type, string m_name); : input.dat 파일을 읽어 한줄(op 1개) 에 대한 return code를 판단 후 output.dat에 적을 string을 리턴해주고 book, undergraduate 벡터에 수정이 필요한 경우 인자들을 Update()함수로 넘겨준다.
    * void Update(int date, string m_type, string m_name, string r_type, string r_name, int op); : check()함수에서 받은 정보를 가지고 book, undergraduate 벡터를 수정하는 함수
    * bool is_registered(string name, string type); : 인자로 받는 이름이 도서관 book 벡터에 등록이 되어있는지 확인하는 함수
    * int DtoInt(string date); : yy/mm/dd 형식의 string 날짜를 int형으로 변환해주는 함수
    * string DtoString(int date); : int형의 날짜를 yy/mm/dd 형식의 string 형식으로 변환해주는 함수
    * void result(); : check 함수에서 받은 string을 ouput.dat 파일에 write해주는 함수

* member(undergraduate)
    * string _name : 멤버 이름
	* map<string, int> _borrow : 멤버가 빌린 resource를 resource name을 키로 가지고 빌린 날짜를 value로 가지는 map 구조로 저장
	* int _restrict_date : 도서관 이용이 언제까지 제한되는지 날짜를 저장 (제한되지 않았을 시 0)

    * 그 외 getter, setter 함수들

* resource(book)
	* string _name : resource 이름
	* string _who_borrow : 빌린 member의 이름(없을시 "")
	* int _borrow_date : 빌린 날짜(없을시 0)

    * 그 외 getter, setter 함수들


