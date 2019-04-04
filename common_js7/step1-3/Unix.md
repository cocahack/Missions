# Unix/Linux



## 알면 좋은 Bash 터미널 단축키

meta 키는 일반적으로 MacOS에서 `esc` 키이며, 터미널 프로그램 설정에서 변경이 가능하다. Windows 에서는 `alt`키를 사용하면 된다.

- `ctrl + a` : 커서를 제일 앞으로 이동
- `ctrl + e` : 커서를 제일 끝으로 이동
- `ctrl + k` : 현재 커서 위치보다 뒤에 있는 모든 텍스트를 제거함
- `ctrl + u` : 입력된 내용을 제거
- `ctrl + l` : 출력된 내용을 위로 밀기(`clear` 명령어와 비교)
- `ctrl + r` : history를 기반으로 명령어를 검색
- `meta + f` : 단어 단위로 오른쪽으로 이동(VIM에서 `w`와 같음) 
- `meta + b` : 단어 단위로 왼쪽으로 이동(VIM에서 `b`와 같음) 
- `meta + d` : 단어 단위로 삭제(VIM에서 `dw`와 같음) 
- `meta + .`: 최근 사용한 명령어의 가장 마지막 단어를 가져올 수 있음. 여러 명령어를 입력해보고 키를 반복해서 눌러볼 것.



## 기본 명령어

- `cp`: 파일을 복사한다.
  - `-r`: 디렉토리 내부의 파일도 같이 복사한다.
- `mv`: 파일을 이동하거나 이름을 변경한다.
- `rm`: 파일 / 디렉토리를 삭제한다.
  -  `-f`: 강제 삭제
  -  `-r`: 디렉토리와 디렉토리 내부의 파일도 포함하여 삭제
  -  `-i`: 프롬프트 출력
- `find`: 지정한 디렉토리에서 원하는 항목(파일명, 수정한 날짜, 생성한 날짜, 크기 등)으로 검색할 수 있다. 자세한 내용은 `man`페이지를 참조할 것.
- `pwd`: 현재 디렉토리 위치를 출력한다.
- `sudo`: 다른 사용자의 권한으로 프로그램을 실행할 수 있도록 도와주는 명령어로, 일반적으로는 root의 권한을 빌려오게 된다.
  - `-i`: 현재 사용자의 비밀번호로 root 사용자 로그인이 가능하다.
- `su`:  현재 사용자를 로그아웃하지 않고 다른 사용자로 로그인할 수 있다. 로그인할 사용자의 계정 이름을 명령어 뒤에 붙여야 하며, 붙이지 않을 경우 root로 간주한다.
  - `su - <username>`: 환경변수까지 다시 적용하여 로그인한다. 
- `mkdir`: 디렉토리를 생성한다.
  - `-p`: 부모 디렉토리까지 같이 생성한다. 즉 `mkdir -p code/squad`처럼 사용할 수 있다.
- `rmdir`: 디렉토리를 제거한다. 디렉토리 내에 파일이 있다면 지울 수 없으며 이때는 `rm -rf`를 사용해야 한다. 
- `man`: 명령어, API, 설정 파일 등의 설명과 사용 방법을 알 수 있다.



## 입출력 리다이렉션

### 기본

- `>`: 출력 대상을 표준 출력에서 파일로 변경한다. 파일이 이미 있을 경우, 기존의 내용은 삭제된다.
- `>>`: 출력 대상을 변경하면서 파일의 내용을 변경하지 않고 파일의 끝부터 쓴다.
- `|`: 왼쪽 명령어의 출력을 오른쪽 명령어의 입력으로 보낸다.
- `2>`: 표준 에러를 리다이렉트 한다. 에러만 따로 파일에 기록할 때 사용한다.
- `2>>`: 표준 에러를 리다이렉트하면서 파일의 끝부터 기록한다.
- `2>&1` : 표준 에러를 표준 출력으로 리다이렉트 한다.
- `<`: 파일의 내용을 입력으로 받는다.

### 심화

#### /dev/null

Null device라고 하며, 입력을 버리는 방식으로 동작한다.

```console
test@0bdd94be5649:~$ find / -name '*a*' > /dev/null
find: '/proc/tty/driver': Permission denied
find: '/proc/1/task/1/fd': Permission denied
find: '/proc/1/task/1/fdinfo': Permission denied
find: '/proc/1/task/1/ns': Permission denied
find: '/proc/1/fd': Permission denied
find: '/proc/1/map_files': Permission denied
find: '/proc/1/fdinfo': Permission denied
find: '/proc/1/ns': Permission denied
find: '/proc/47/task/47/fd': Permission denied
find: '/proc/47/task/47/fdinfo': Permission denied
find: '/proc/47/task/47/ns': Permission denied
find: '/proc/47/fd': Permission denied
find: '/proc/47/map_files': Permission denied
find: '/proc/47/fdinfo': Permission denied
find: '/proc/47/ns': Permission denied
find: '/var/cache/ldconfig': Permission denied
find: '/var/cache/apt/archives/partial': Permission denied
find: '/root': Permission denied
```

출력 내용은 모두 지워지고 에러 내용만 출력된다.

#### <<

Here-document라고 한다. 다음 3가지 사용법이 있다.

```console
### 쉘 변수에 multi-line 문자열을 저장.
$ sql=$(cat <<EOF
SELECT foo, bar FROM db
WHERE foo='baz'
EOF
)

### 파일에 여러 줄 쓰기. 스크립트 내용 중 파일 에디트가 필요할 때 정말 유용하다.
$ cat << EOF > /etc/exports
/foo 192.0.2.0/24(rw)
EOF

### 파이프에 multi-line 문자열 전달.
$ cat <<EOF | grep 'b' | tee b.txt
foo
bar
baz
EOF
```

#### <<<

문자열을 명령어의 표준 출력으로 전달한다.

```console
$ bc <<< 1+1
2
```



## 파일 시스템 구조

[![Image result for rhel 7 file system hierarchy](https://lh3.googleusercontent.com/-MVKJC6xREvI/VrjBDeauSXI/AAAAAAAABe8/9vdhVscw-xI/s800-Ic42/centos7-filesystem.png)](https://elearning.wsldp.com/pcmagazine/centos-7-filesystem-hierarchy/)

- `/etc`: 프로그램과 패키지를 위한 설정 파일이 들어 있다.
- `/var`: 가변 데이터가 저장되는 곳이다. 일반적으로 로그 파일이 여기에 위치한다.
- `/run`: 프로세스를 위한 런타임 데이터가 저장된다.
- `/home`: 홈 디렉토리가 위치하는 곳이다.
- `/root`: `root` 사용자의 홈 디렉토리이다.
- `/tmp`: 임시 파일이 저장되는 곳이다. 10일 이후 삭제된다.
- `/boot`: 시스템 부트 프로세스를 시작할 때 필요한 파일들이 저장되어 있다.
- `/dev`: 필수 디바이스에 대한 정보가 들어있다.



## 원격 시스템 접근

- `ssh user@server`: 원격 호스트에 연결한다.
  - `-X`: X11 포워딩을 활성화한다. 서버의 GUI 프로그램을 로컬 환경에서 사용할 수 있게 된다. 서버가 GUI 환경이어야 하고, X11 연결을 허용하는 구성이 되어 있어야 하며, 클라이언트의 경우에 MacOS에서는 [이것](https://www.xquartz.org/)이 필요하고, Windows는 [이걸](http://www.straightrunning.com/XmingNotes/) 사용해야 한다.
- `ssh server command`: 원격 호스트에 연결하지 않고 명령어만 실행한다.
- `scp`: 원격으로 파일을 전송할 때 사용한다.
  - `scp filename user@server:PATH`: 로컬 파일을 원격 호스트의 PATH로 복사한다.
  - `scp user@server:FILEPATH PATH`: 원격 호스트의 파일을 로컬로 가져온다.
  - `-r`: 디렉토리 내의 모든 폴더를 포함한다.



## 아카이브 및 압축

- `tar`: 파일을 아카이브화 한다. 압축 기능이 아니다.
  - `-c`: 새로운 아카이브를 생성한다.
  - `-t`: 아카이브의 내용물을 리스트로 보여준다.
  - `-x`: 아카이브에서 파일을 추출한다.
  - `-z`: `gzip`으로 압축하거나 압축을 푼다.
  - `-v`: 작업 내용을 자세하게 출력한다.
  - `-j`: `bzip`으로 압축하거나 압축을 푼다.
  - `-J`: `xz`로 압축하거나 압축을 푼다.
  - `-f`: 작업할 파일이나 아카이브를 명시할 때 사용한다.
  - 예시
    - tar -tf helloworld.tar: 아카이브의 모든 파일을 한 줄 씩 출력한다.
    - tar -xf helloworld.tar: 아카이브에서 파일을 추출한다.
    - tar -czvf helloworld.tar.gz hello world: hello와 world 파일을 helloworld.tar.gz로 압축한다.
    - tar -xzvf helloworld.tar.gz: 압축을 푼다.
- `zip`: `zip`으로 압축할 때 사용한다.
- `unzip`: `zip`으로 압축된 파일을 해제할 때 사용한다.



## 하드 링크 및 소프트 링크



## 권한



## 시스템 문서 읽고 쓰기



## 프로세스 다루기



## 로그 파일 및 저널



## 작업 스케줄링





## Shell script

[bash-handbook](https://github.com/denysdovhan/bash-handbook/blob/master/translations/ko-KR/README.md#while-loop)를 참고하여 스크립트 프로그래밍

**구구단을 출력하는 bash 프로그램**

```bash
#!/bin/bash

if [ -z $1 ]
then
    echo "Usage: ./mul_table <NUMBER>"
    exit 1
fi

for i in $(seq 1 9)
do
    printf "%d X %d = %d\n" $1 $i $(( $1 * $i ))
done
```



**Add, commit, push 한번에 하기**

```bash
#!/bin/bash

 read -p "Enter the commit message: " message

 git add -A
 git commit -m $message
 git push origin master
```

커밋 메시지가 완전히 출력되지 않아서 수정이 필요함.
