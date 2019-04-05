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
- `rmdir`: 디렉토리를 제거한다. 디렉토리 내에 파일이 있다면 지울 수 없으며 이럴 때는 `rm -rf`를 사용해야 한다. 
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

Null device라고 하며, 입력을 버리는 방식으로 동작한다. 리눅스에서는 디바이스도 파일로 다루기 때문에 리다이렉트가 가능하다.

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

위의 예제는 표준 에러만 출력하는 것을 보여준다.

#### <<

Here-document라고 한다. 다음 3가지 사용법이 있다.

```console
### 쉘 변수에 multi-line 문자열을 저장.
$ sql=$(cat <<EOF
SELECT foo, bar FROM db
WHERE foo='baz'
EOF
)

### 파일에 여러 줄 쓰기. Bash 스크립트에서 중 파일 에디트가 필요할 때 정말 유용하다.
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
- `/var`: 가변 데이터가 저장되는 곳이다. 일반적으로 로그 파일이 여기에 위치하며, Apache 웹 서버의 기본 디렉토리가 위치하는 곳이다. 
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

- `tar`: 파일을 아카이브화 한다. 압축 기능이 아니며, 다른 옵션과 같이 써야 압축 기능을 사용할 수 있다.
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

- 하드 링크(hard link): 시스템에 존재하는 파일을 참조하는 새로운 진입점(entry)를 만들기 위해 `inode`와 직접 연결한 것을 말한다.
- 소프트 링크(symlinks, soft links): 윈도우즈의 바로가기와 비슷하다. 

### 명령어

- `ln` : 파일을 연결한다.
  - `-s`: 소프트 링크를 만든다.
  - `-s`을 사용하지 않으면 하드 링크를 만든다.

### 예시

빈 파일 3개를 만들고 각각의 `inode`를 확인한다.

```console
$ touch {a..b}.txt
$ echo "a text file" > a.txt
$ echo "b text file" > b.txt
$ ls
a.txt b.txt
$ ls -i
8595775213 a.txt 8595775214 b.txt
```

`a.txt`의 하드 링크를 만들고 inode를 확인한다.

```console
$ ln a.txt hard_link_a.txt
$ ls -i
8595775213 a.txt           8595775214 b.txt           8595775213 hard_link_a.txt
```

원본 파일과 하드 링크 파일의 inode가 같은 것을 확인할 수 있다. b.txt 에 소프트 링크를 만들고 inode를 확인한다.

```console
$ ln -s b.txt soft_link_b.txt
$ ls -i
8595775213 a.txt           8595775214 b.txt           8595775213 hard_link_a.txt 8595775264 soft_link_b.txt
```

Inode 값이 다른 것을 확인할 수 있다. 이 상태에서 b.txt 파일을 제거하고 소프트 링크 파일을 cat으로 출력하면 다음과 같다.

```console
$ ls
a.txt           b.txt           hard_link_a.txt soft_link_b.txt
$ cat soft_link_b.txt
b text file
$ rm -f b.txt
$ cat soft_link_b.txt
cat: soft_link_b.txt: No such file or directory
```

원본 파일이 지워졌기 때문에 파일이 존재하지 않는다는 에러 메시지를 볼 수 있다. 이번에는 a.txt 파일을 제거한다.

```console
$ cat hard_link_a.txt
a text file
$ rm -f a.txt
$ cat hard_link_a.txt
a text file
```

원본 파일이 지워졌어도 같은 inode를 참조하는 하드 링크 파일이 존재하기 때문에 파일의 내용에 접근할 수 있다.

## 권한

### 개념

권한을 정의하는 방법은 두가지가 있다.

- `u`, `g`, `o`, `r`, `w`, `x` 등 Symbolic character
- Octal bit

터미널을 열고 임의의 디렉토리에 들어가서 `ls -l`을 입력하면 다음과 같다.

```console
$ ls -l
total 0
-rw-r--r--  1 mcc  staff     0B  4  5 16:18 a.txt
-rw-r--r--  1 mcc  staff     0B  4  5 16:18 b.txt
-rw-r--r--  1 mcc  staff     0B  4  5 16:18 c.txt
drwxr-xr-x  2 mcc  staff    64B  4  5 16:19 dir
```

각각의 컬럼이 뜻하는 것은 파일의 권한, 하드링크의 개수,  소유자,  그룹,  마지막으로 수정한 시각, 파일명이다.

아래의 그림은 파일의 권한을 해석하는 방법을 보여준다.

![Image result for linux permission](https://www.pluralsight.com/content/dam/pluralsight/resources/blog/2011/12/linux-file-permissions/wp/img/Linux-File-Permissions-2.jpg)

가장 첫 비트는 파일의 종류를 나타낸다. 다음 9개의 비트는 3개씩 묶어서 소유자의 권한, 그룹의 권한, 소유자와 그룹에 속하지 않은 다른 사용자의 권한이다.

3개의 비트에서 첫번째 비트는 읽기 권한이고 두번째 비트는 쓰기 권한, 마지막 비트는 실행 권한이다. 

각 비트가 의미하는 것이 파일과 디렉토리에서 미묘하게 다르다. 각 비트가 설정되어 있지 않을 때 어떤 일이 일어나는 지를 표로 정리하면 다음과 같다.

| 유형     | 읽기(r)                  | 쓰기(w)                        | 실행(x)                          |
| -------- | ------------------------ | ------------------------------ | -------------------------------- |
| 파일     | 파일 읽기 불가(cat 등)   | 파일 수정 불가(vim 저장 불가)  | script나 바이너리 파일 실행 불가 |
| 디렉토리 | ls로 파일 목록 조회 불가 | 디렉토리에 파일 생성/삭제 불가 | 대부분의 명령어를 사용할 수 없음 |

파일의 권한을 rwx와 같이 문자로 나타내기도 하지만 숫자로도 나타낼 수 있다. `r`을 `4`로, `w`를 `2`로 그리고 `x`를 `1`로 각각 대응시킨다. 이 규칙을 적용해서 위의 그림을 숫자로 나타내면 `744`가 된다.

### 명령어

- `chmod`: 파일이나 디렉토리의 권한을 변경한다.
  - `u`: 소유자
  - `g`: 그룹
  - `o`: 기타 사용자
  - `a`: u, g, o 모두 포함
  - `r`: 읽기
  - `w`: 쓰기
  - `x`: 실행
  - `s`: UID 또는 GID 설정
  - `t`: Sticky bit
  - `-X`: 권한 변경을 디렉토리에만 적용하도록 강제하는 옵션
  - `octal bits`
    - `1`: 실행
    - `2`: 읽기
    - `4`: 읽기

### 예제

```console
$ touch {a..c}.txt
$ mkdir dir
$ ls -l
total 0
-rw-r--r--  1 mcc  staff     0B  4  5 17:11 a.txt
-rw-r--r--  1 mcc  staff     0B  4  5 17:11 b.txt
-rw-r--r--  1 mcc  staff     0B  4  5 17:11 c.txt
drwxr-xr-x  2 mcc  staff    64B  4  5 17:11 dir
$ chmod u+x a.txt
$ ls -l a.txt
-rwxr--r--  1 mcc  staff     0B  4  5 17:11 a.txt
$ chmod g-r b.txt
$ ls -l b.txt
-rw----r--  1 mcc  staff     0B  4  5 17:11 b.txt
$ chmod 400 c.txt
$ ls -l c.txt
-r--------  1 mcc  staff     0B  4  5 17:11 c.txt
$ chmod u-w dir
$ touch dir/test
touch: dir/test: Permission denied
$ chmod u-x dir
$ cd dir
cd: permission denied: dir
$ chmod u+s a.txt
$ ls -l a.txt
-rwsr--r--  1 mcc  staff     0B  4  5 17:11 a.txt
$ chmod g+s b.txt
$ ls -l b.txt
-rw---Sr--  1 mcc  staff     0B  4  5 17:11 b.txt
$ chmod 1640 c.txt
$ ls -l c.txt
-rw-r----T  1 mcc  staff     0B  4  5 17:11 c.txt
```

### 파일 소유자, 그룹 변경

- `chown`: 소유자 또는 그룹을 변경한다.
  - `chown username file`: 파일의 소유자를 변경
  - `chown username:group file`: 파일의 소유자와 그룹을 한번에 변경
  - `chown username: file`: 파일의 소유자와 그룹을 username으로 변경
- `chgrp`: 파일의 그룹을 변경.

## 프로세스 다루기

- `top`: 윈도우즈의 작업 관리자의 CUI 버전이라고 생각하면 된다.
  - `k`: 프로세스 kill
  - `q`: 나가기
  - `r`: 프로세스 우선순위 
  - `P`: CPU 사용량으로 정렬
  - `M`: Memory 사용량으로 정렬
  - `l`: 부하 평균 토글
  - `t`: Task 디스플레이 토글
  - `m`: Memory 디스플레이 토글
  - Column
    - PID: 프로세스 ID
    - USER
    - PR: 커널이 보는 프로세스의 실제 우선순위.
    - NI: Niceness. 커널에게 프로세스가 어떤 우선순위를 가져야 하는지를 알려주는 힌트정도로 생각하면 된다. -20부터 19까지의 값을 가진다. 값이 낮을수록 높은 우선순위이다.
    - VIRT: 가상 메모리 크기
    - RES: Non-swap 메모리 크기
    - SHR: 공유 메모리 크기
    - %CPU: CPU 점유율
    - %MEM: 메모리 점유율
    - TIME+: 프로세스 시작 후 경과한 시간
- `pgrep`: 프로세스를 검색한다.
  - `-u`: 사용자 이름으로 검색
  - `-l`: 프로세스 이름 출력
- `kill`: 프로세스에 시그널을 보낸다.
  - `-l`: 시그널 목록 출력
  - `SIGHUP`: 프로세스를 종료하지 않고 설정을 다시 로드한다.
  - `SIGINT`: `ctrl+c`. 키보드로 인터럽트를 보내 프로세스를 종료한다.
  - `SIGKILL`: 프로세스를 즉시 종료한다. 되도록이면 사용하지 말아야 한다.
  - `SIGTERM`: 프로세스를 종료하라는 요청을 보낸다. 요청은 무시될 수도 있다.
  - `SIGCONT`: 이전에 중단했던 프로세스를 재시작한다.
  - `SIGSTOP`: 프로세스를 중지한다.
- `ps`: 프로세스 상태를 확인한다.
  - 주로 사용하는 조합
    - `ps -ef`
    - `ps aux`

## 작업 스케줄링

### at 

명령어를 나중에 실행한다.

#### 관련 설정파일 

- `/etc/at.allow`: `at`명령어를 사용할 수 있는 사용자 목록. 기본값은 비어 있음(모두 허용).
- `/etc/at.deny`: `at` 명령을 사용할 수 없는 계정 목록. 기본값은 비어 있음(모두 허용).

#### 예시

```console
$ at 9:00 AM
at> sh backup.sh
at> ^d
job 3 at 2013-03-23 09:00
```

### crontab

- `-e`: vi`편집기가 열린다. 여기에 반복할 명령어와 반복될 주기를 입력하고 저장하면 cron 작업이 생성된다.
- `-l`: 작업 목록을 출력한다.
- `-r`: 작업을 삭제한다.

#### 예시

```console
# crontab -e
SHELL=/bin/bash
MAILTO=root@example.com
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin

# For details see man 4 crontabs

# Example of job definition:
# .---------------- minute (0 - 59)
# |  .------------- hour (0 - 23)
# |  |  .---------- day of month (1 - 31)
# |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
# |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri,sat
# |  |  |  |  |
# *  *  *  *  * user-name  command to be executed

# backup using the rsbu program to the internal 4TB HDD and then 4TB external
01 01 * * * /usr/local/bin/rsbu -vbd1 ; /usr/local/bin/rsbu -vbd2

# Set the hardware clock to keep it in sync with the more accurate system clock
03 05 * * * /sbin/hwclock --systohc

# Perform monthly updates on the first of the month
```

## 기타 명령어

- `which`: 명령어의 위치를 보여줌
- `whatis`: 매뉴얼 페이지의 설명을 보여줌
- `w`: 현재 접속한 사용자와 uptime, 부하 평균 등을 보여줌
- `uptime`: `w`에서 접속한 사용자를 뺀 나머지 정보를 보여줌
- `whoami`: 현재 로그인한 사용자의 이름 출력
- `last`: 사용자의 로그인 기록, 시스템 다운, 리부팅 시간을 조회할 수 있다.
- `date`: 현재 시간 출력. 다양한 포맷이 존재한다.
- `hwclock`: 하드웨어 시간 출력. `-w`로 현재 시간을 하드웨어 시간과 동기화할 수 있다.



## Shell script

[bash-handbook](https://github.com/denysdovhan/bash-handbook/blob/master/translations/ko-KR/README.md#while-loop)를 참고

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
