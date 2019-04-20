const todos = [
  {
    name: "자바스크립트 공부하기",
    tags: ["programming", "javascript"],
    status: "todo",
    id: 12123123
  },
  {
    name: " 그림 그리기",
    tags: ["picture", "favorite"],
    status: "doing",
    id: 312323
  },
  {
    name: "IOS 공부하기",
    tags: ["programming", "ios"],
    status: "todo",
    id: 3123233
  },
  {
    name: "글쓰기",
    tags: ["writing", "hobby"],
    status: "doing",
    id: 31232311
  },
  {
    name: "운동",
    tags: ["health", "hobby"],
    status: "done",
    id: 312323555
  }
];


const rl = require('readline');
const promptMsg = "명령하세요 : ";

rl = readline.createInterface(process.stdin, process.stdout);

rl.setPrompt(promptMsg);
rl.prompt();

rl.on('line', function(command) {
  const parsedCmd = command.split('$');
  const operation = parsedCmd[0];
  const args = parsedCmd.slice(1);
  
  if(operation === "exit"){
    rl.close();
  }
  
  rl.prompt();
}).on('close', function() {
    process.exit(0);
});