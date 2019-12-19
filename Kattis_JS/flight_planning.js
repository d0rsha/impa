const readline = require("readline")

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
})

// Globals
let N = null
let rlcounter = 0
let nodes = []

rl.on("line", line => {
  if (N === null) {
    console.log("Gimme more input shitace")
    N = Number(line)
    rlcounter = N
  } else {
    rlcounter--
    console.log(rlcounter)

    let [from, to] = line.split(" ")

    nodes[from] = nodes[from] ? [...nodes[from], to] : [to]
    nodes[to] = nodes[to] ? [...nodes[to], from] : [from]
  }

  if (rlcounter === 1) {
    // Run algorithm
    console.log(nodes)

    let lPair = bfsMostDistantNode(1)
    console.log(lPair.index)
    let rPair = bfsMostDistantNode(lPair.index)

    let removeEdge = maximizeLeftRight(rPair.index, rPair.max)

    console.log("Slut")
    rl.close()
  }
})

function bfsMostDistantNode(start) {
  start = start
  let distanceTo = []
  for (let i = 1; i <= N; i++) {
    distanceTo[i] = -1
  }

  let q = []
  q.push(start)
  distanceTo[start] = 0

  while (q.length > 0) {
    console.log("queue", q)
    let cand = q.shift()
    let dist = distanceTo[cand] + 1

    let list = nodes[cand]
    if (list) {
      for (let i = 0; i < list.length; i++) {
        let element = list[i]
        if (distanceTo[element] !== -1) continue

        q.push(element)
        distanceTo[element] = dist
      }
    }
  }

  let max = 0
  let maxIndex = 0
  console.log("distanceTo", distanceTo)
  distanceTo.forEach((element, idx) => {
    if (element > max) {
      max = element
      maxIndex = idx
    }
  })
  return { max: max, index: maxIndex }
}

function maximizeLeftRight(leftIdx, lPath) {
  let half = Math.ceil(lPath / 2)
  distanceTo = []
  for (let i = 1; i <= N; i++) {
    distanceTo[i] = -1
  }

  let q = []
  let nodeCunter = 1
  q.push(leftIdx)
  distanceTo[leftIdx] = 0

  while (q.length > 0) {
    let cand = q.shift()
    let dist = distanceTo[cand] + 1

    let list = nodes[cand]
    if (list) {
      for (let i = 0; i < list.length; i++) {
        let element = list[i]
        if (distanceTo[element] !== -1) continue
        if (dist > half) {
          // remove cand -> element
          delete list[i]
          break
        }
        q.push(element)
        distanceTo[element] = dist
        nodeCunter++
      }
    }
  }
}
