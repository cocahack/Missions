(function callModuleChecker(){
  var result = new Date();
  console.log("WELCOME UTIL MODULE : " + result);
})();

function checkNumber(target){
  return typeof target === 'number';
}

module.exports.sum = (arr) => {
  let result = 0;

  for (let i = 0; i < arr.length; i++) {
        result += checkNumber(arr[i]) ? arr[i] : 0;
  }

  return result;
}
