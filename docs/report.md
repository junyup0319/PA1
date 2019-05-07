# # PA1: TAsh 201421023_홍준엽
## 인적사항
* 사이버보안학과
* 201421023
* 홍준엽

## 과제 수행 정도
### 기본 shell 들의 기능 - 완료
* Process creation
* File redirection
* Environmental variable

### 채점 보조 기능 - 완료
* ready-to-score
* auto-grade-pa0
* report-grade


## 과제를 수행하면서 배운 것
#### process 관리
* process 생성 : fork() & vfork()
* process 대기 : wait() & waitpid()
* process 종료 : exit()
* exec 계열 함수들
	* execl, execlp, execv, execvp 함수 존재
	* 'l' 이 붙으면 인자를 나열, v가 붙으면 인자를 배열로 넣는다
	* 'p' 가 붙으면 환경변수에 있는 프로그램이 실행된다. 없으면 경로를 지정

#### 여러 shell의 기능
* 기존에 사용하던 cd, ls 외에 grep, echo pwd 등의 명령을 배울 수 있었다.

#### 버퍼
* fflush(): 버퍼를 비우는 함수
* 하지만 fflush는 출력버퍼를 비우기 위한 함수이므로 입력버퍼를 비우고 싶을때는 `while(getchar()!='\n') continue;` 실행
* fflush(stdin)은 결과를 알 수 없고 정의되지 않은 방법!

#### gets() & fgets()
* gets는 입력을 어디까지 받을지 알 수 없으므로 저장될 버퍼가 작다면입력을 다 받지 못하고 잘릴 수 있다. 따라서 얼마나 입력을 받을지 지정할 수 있는 fgets 를 사용하는 것이 좋다

#### ubuntu 와 macOS 차이
* mac 에서는 /usr/bin/grep이 존재
* ubuntu 에서는 /bin/grep이 존재

## 과제에 대한 피드백
* 이번 과제를 진행하면서 fgets의 인자 값으로 넣어준 버퍼를 직접 사용하면 입력 오류가 나는 경우가 있었다. 이를 리턴값인 char*로 받아서 사용하면 문제를 해결할 수 있었다.
* child process를 만들면 버퍼 값의 오류? 가 나는 경우가 생겼다. 이때 fflush(stdout)을 사용함으로써 문제를 해결할 수 있었다.
