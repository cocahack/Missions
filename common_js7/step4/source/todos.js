const todosFunctions = {
};

function printResult(result, query) {
  let str = "";
  if (query === "all") {
    str = `현재 상태: ${ Object.entries(result).map(v => `${v[0]} : ${v[1]}`).join(", ")}`;
  } else {
    str = `${query} 리스트 : 총${result.length}건 : ${result.join(", ")}`;
  }
  console.log(str);
}

const showTodos = query => {
  let show_result;
  if (query === "all") {
    show_result = todos.reduce((a, e) => {
      a[e.status] = a[e.status] + 1 || 1;
      return a;
    }, {});
  } else {
    show_result = todos.filter(v => v.status === query).map(v => v.name);
  }
  printResult(show_result, query);
};


module.exports = ( () => {
  const _todos = Symbol('todos array');
  const _init = Symbol('TodoManager init function');

  class TodoManager {
    constructor(){
      this[_todos] = [];

      this[_init] = () => {

      }
    }
  }
})();