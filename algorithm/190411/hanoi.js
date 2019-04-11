function hanoi(n, source, dest){
  const aux = 6 - source - dest;
  if(n === 0){
    // console.log(`${n} moved from ${source} to ${dest}`);
    return;
  }
  hanoi(n - 1, source, aux);
  console.log(`${n} moved from ${source} to ${dest}`);
  hanoi(n - 1, aux, dest);
}

hanoi(3, 1, 3, 2);