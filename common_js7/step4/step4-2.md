# Step 4-2. 비동기 프로그래밍

## Node.js 비동기 기본

### 비동기

자바스크립트는 하나의 스레드만 사용할 수 있다. 이는 Call stack을 한 개만 가지고 있고 한 번에 하나의 작업만 할 수 있다는 뜻이다. 이러한 한계를 극복하기 위해 비동기를 사용한다.

### 이벤트 기반(Event-Driven) 시스템

이벤트가 발생하면 미리 저장되어 있던 함수를 수행하는 방식이다. 이벤트가 발생할 때 실행할 함수를 지정하는 것을 **이벤트 리스너**에 **콜백 함수**를 등록한다고 한다. 

### Event loop, Task queue, Background

- 이벤트 루프: 이벤트가 발생할 때 실행되는 함수들을 관리하고, 콜백 함수의 실행 순서를 결정한다. 
- 태스크 큐: 이벤트 발생 후 실행되어야 할 함수들이 여기에 저장된다. 콜백 함수가 큐에 들어가는 순서는 이벤트 루프가 결정한다.
- 백그라운드: 타이머나 I/O 태스크 콜백, 이벤트 리스너가 대기하는 곳이다.

### Non-Blocking I/O 

**Non-blocking** 은 이전 작업을 기다리지 않고 다음 작업을 수행하는 것이다. 따라서 동시간에 여러 작업을 할 수 있게 되는 것이다. 하지만 싱글 스레드를 사용하는 자바스크립트 환경에서는 non-blocking을 사용해도 모든 작업에 시간적으로 이득을 볼 수는 없다. 따라서 비교적 작업시간이 긴 I/O 작업에 이를 적용한다. I/O 작업에는 파일 시스템에서 파일을 조작하거나 네트워크로 요청을 날리는 등의 작업이 있다. 

### 프로세스와 스레드

#### 프로세스

파일 시스템에 저장되어 있는 프로그램을 실행하면 메인 메모리로 로드된다. 메인 메모리에 로드된 프로그램의 인스턴스를 프로세스라고 한다. 

#### 스레드

프로세스에 존재하는 실행 흐름으로 프로세스는 한 개의 스레드를 가질 수도 있고, 여러 개의 스레드를 가질 수도 있다. 각 스레드는 각자의 스택을 가진다. 또한 프로세스 내부에 존재하므로 프로세스가 사용할 수 있는 자원(메모리 등)을 공유할 수 있다. 

#### 프로세스 간 메모리 공유

기본적으로 프로세스 간 메모리 공유는 불가능하다. 이를 가능케하는 솔루션이 필요하며 대표적으로는 [Redis](https://redis.io/)가 있다.

## Node.js 아키텍처

### Multi-threaded Request-response 아키텍처

Java, PHP 등 다른 언어에서는 멀티 스레드를 사용한 아키텍처가 기본이다.

#### Request-response Model

클라이언트가 서버로 요청을 보내면 서버는 이에 대한 응답을 보내는 방식이다. 이 때 **HTTP 프로토콜**을 사용한다. HTTP 프로토콜은 대표적인 **Stateless 프로토콜**이다. Stateless 프로토콜은 이전 요청에 대한 어떠한 정보도 저장하지 않기 때문에, 각각의 요청을 독립적인 트랜잭션으로 취급한다. HTTP 프로토콜이 Stateless 프로토콜이므로 Request-response model도 **stateless model**이다. 

#### Request-response Model의 처리 순서

1. 클라이언트는 서버로 요청을 보낸다.
2. 서버는 클라이언트의 요청을 처리하기 위한 **스레드 풀**을 가지고 있다.
3. 서버는 클라이언트의 요청을 기다리며 끝없이 루프를 돈다.
4. 서버가 요청을 받으면
   - 서버는 클라이언트의 요청 중 하나를 선택한다.
   - 스레드 풀에서 스레드 하나를 선택한다.
   - 클라이언트의 요청을 스레드에 할당한다.
   - 이 스레드는 클라이언트의 요청을 읽은 뒤, Blocking I/O 작업을 포함한 클라이언트의 요청을 처리한 뒤 클라이언트에게 보낼 응답을 준비한다.
   - 스레드는 서버로 준비된 응답을 보낸다.
   - 서버는 클라이언트에게 이 응답을 보낸다.

#### Request-response Model Diagram

![Request-response model diagram](https://cdn.journaldev.com/wp-content/uploads/2015/04/Request-Response-Model.png)

- 클라이언트는 서버로부터 서비스를 받기 위해 요청을 보내며, 동시에 여러 명의 클라이언트가 요청을 보낼 수 있다. 위의 그림에서는 `n`명의 클라이언트가 요청을 보내는 것으로 나타나있다. 
- 웹 서버는 내부적으로 스레드 풀에 `m`개의 스레드를 가지고 있는 상태이다. 
- 웹 서버는 여러 요청을 한 번에 하나 씩 처리한다.
  - 웹 서버가 `client-1` 의 요청 `request-1` 을 선택하면, 스레드 풀에서 `thread t-1` 을 할당한다.
    - `thread t-1` 은 `request-1` 을 읽고 이를 처리한다.
    - Request에 Blocking I/O 가 필요하지 않으면
      - 필요한 작업을 수행하고
      - 클라이언트에게 줄 `response-1` 을 준비한 뒤 서버에 돌려준다.
    - Blocking I/O가 필요하면
      - Thread는 외부 시스템과의 상호작용을 위한 시간이 필요하다.
      - 외부 시스템과의 작업을 마친 뒤 남은 작업을 수행하고
      - 클라이언트에게 줄 `response-1` 을 준비한 뒤 서버에 돌려준다.

`n` 이 `m` 보다 크다면 서버는 사용할 수 있는 스레드 전부를 클라이언트의 요청에 할당한다.  `m` 개의 스레드를 모두 사용하면 남은 클라이언트의 요청은 스레드가 자신에게 할당된 요청에 대한 모든 작업을 수행하고 다음 요청을 수행할 수 있는 상태가 될 때까지 큐에서 대기한다.

스레드가 Blocking I/O 작업에 많은 시간을 소모하게 되면 큐에 대기하고 있는 다른 요청들에게도 영향을 미치게 된다.

각각의 스레드는 메모리 등 많은 자원을 활용한다. 스레드가 작업을 마치고 바쁜 상태(busy state)에서 대기 상태(waiting state)로 전환될 때, 사용하고 있던 모든 자원을 다른 스레드도 사용할 수 있도록 놔줘야 한다.

####  Request-response Stateless Model의 단점

- 클라이언트의 요청을 동시에 처리하기가 어렵다.
- 동시에 들어오는 요청이 많아지면 스레드를 더 많이 사용해야 하고, 이는 메모리 사용량의 증가로 이어진다.
- 가용한 스레드가 없어서 요청을 보내도 대기하고 있어야 할 수도 있다.
- Blocking I/O를 처리하는데 시간을 낭비하게 된다.

### Node.js의 아키텍처 - Single threaded event loop

##### Single threaded event loop model의 처리 과정

- 클라이언트는 웹 서버로 요청을 보낸다.
- Node.js 웹 서버는 내부적으로 스레드 풀을 가지고 있다.
- 웹 서버는 요청을 받고 이를 큐에 넣는다. 이 큐를 **Event Queue** 라고 한다.
- Node.js 내부에 존재하는 **Event loop**는 하나의 스레드만 사용한다. Event loop는 Event queue에 클라이언트의 요청이 있는지 확인한다.
  - 요청이 없다면, 들어올 때까지 기다린다.
  - 요청이 있다면,
    - 클라이언트의 요청에 대한 처리를 시작한다.
    - 클라이언트의 요청을 처리하는 데 Blocking I/O가 필요하지 않다면, 요청을 처리하고 응답을 클라이언트에게 보낸다.
    - 클라이언트의 요청에 Blocking I/O가 필요하다면 
      - 스레드 풀에서 사용할 수 있는 스레드가 있는지 확인한다.
      - 스레드 하나를 선택해서 사용자의 요청에 할당한다.
      - 스레드는 할당된 요청을 처리하고, Blocking I/O를 수행한 뒤, 응답을 준비하고 이를 event loop로 보낸다.
      - Event loop는 클라이언트에 응답을 보낸다.

#### Single threaded event loop model diagram

![Node.js Architecture](https://cdn.journaldev.com/wp-content/uploads/2015/04/NodeJS-Single-Thread-Event-Model.png)

- `n` 명의 클라이언트가 동시에 접속한다고 가정한다. 

- 웹 서버는 스레드 풀을 가지고 있으며 `m` 개의 스레드가 존재한다.

- 웹 서버는 클라이언트의 요청을 event queue에 넣는다.

- Event loop는 요청을 하나씩 선택하여 처리한다.

  - Blocking I/O가 필요하지 않은 경우

    Event loop가 `request-1` 을 선택하고 Blocking I/O 또는 다른 복잡한 작업이 필요한지 확인한다.

    -  `request-1` 은 간단한 작업이고 blocking I/O가 필요하지 않으므로 별도의 스레드가 필요하지 않다.
    - Event loop는 요청에 필요한 모든 작업을 처리하고 `response-1` 을 준비한다.
    - Event loop는 `response-1` 을 `client-1` 에게 보낸다.

  - Blocking I/O가 필요한 경우

    - Event loop가 `request-n` 을 선택하고 Blocking I/O 또는 다른 복잡한 작업이 필요한지 확인한다.
    -  `request-n` 은 복잡한 작업이고 blocking I/O가 필요하므로 event loop는 이 요청을 처리하지 않는다.
    - Event loop는 `thread t-1` 에 `request-n` 을 할당한다.
    - `Thread t-1` 은 `request-n ` 을 읽고 처리한다. 복잡한 작업이나 Blocking I/O 작업을 처리하고 `response-n` 을 준비한다.
    - `Thread t-1` 은 `response-n` 을 event loop로 전달한다.
    - Event loop는 `client-n` 에게 `response-n` 을 전달한다.

#### Single threaded event loop model의 장점

1. 클라이언트의 요청을 동시에 다루는 작업을 쉽게 할 수 있다.
2. Event loop의 특성 때문에, 클라이언트의 요청이 많아도 스레드를 생성할 필요가 없다.
3. 스레드를 적게 사용하기 때문에 자원 소모량이 적다.



## 동기와 비동기에서 Call Stack 탐색

### 동기

```javascript
const baseData = [1,2,3,4,5,6,100];

function foo() {
  baseData.forEach((v,i) => {
    console.log("sync ", i);
    bar();
  });
}

function bar() {
  baseData.forEach((v,i) => {
    console.log("sync 2", i);
  });
}

foo();
```

코드를 실행하면 `foo` 내부에서 `baseData` 의 요소를 하나씩 순회하면서 `bar` 함수를 호출하게 될 것이다. 따라서 출력되는 결과는 항상 아래처럼 나올 것이다.

```console
$ node test.js
sync  0
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
sync 2 5
sync 2 6
sync  1
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
sync 2 5
sync 2 6
sync  2
sync 2 0
sync 2 1
sync 2 2
sync 2 3
sync 2 4
...
```

Call stack을 그림으로 나타내면 다음과 같다. `foo` 에서 `forEach` 로 배열을 순회하면서 `bar` 함수를 반복적으로 호출하게 된다. 

<img width="986" alt="image-20190416113745820" src="https://user-images.githubusercontent.com/18232901/56178168-34b39780-603c-11e9-8e5b-eb5e33ca889e.png">



#### 중첩된 setTimeout

```javascript
const baseData = [1,2,3,4,5,6,100];

const asyncRun = (arr, fn) => {
   arr.forEach((v,i) => {
     setTimeout(() => {
       setTimeout(() => {
         console.log("cb 2");
         fn(i)
        },1000);
       console.log("cb 1");
     }, 1000);
   });
}

asyncRun(baseData, idx =>console.log(idx))
```

콜 스택, 백그라운드 타이머, 콜백 큐, 이벤트 루프를 사용하여 실행 흐름을 나타내었다.

![nested-setTimeout](https://user-images.githubusercontent.com/18232901/56403902-8f4c2e00-629e-11e9-95d5-dd05cd9d1cbf.gif)





## Reference

### Link

[콜 스택과 이벤트 루프 - Zerocho](https://www.zerocho.com/category/JavaScript/post/597f34bbb428530018e8e6e2)

[Stateless Protocol - Wikipedia](https://ko.wikipedia.org/wiki/%EB%AC%B4%EC%83%81%ED%83%9C_%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C)

[Node.js architecture](https://www.journaldev.com/7462/node-js-architecture-single-threaded-event-loop)

### 서적

[Node.js 교과서 - Zerocho](http://www.kyobobook.co.kr/product/detailViewKor.laf?ejkGb=KOR&mallGb=KOR&barcode=9791160505221&orderClick=LAG&Kc=)

