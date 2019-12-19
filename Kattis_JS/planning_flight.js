const readline = require("readline")

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
})

///////////
// Globals
let N = null
let rlcounter = 0
let nodes = []

rl.on("line", line => {
  if (N === null) {
    N = Number(line)
    rlcounter = N
  } else {
    rlcounter--

    let src = Number(line.split(" ")[0])
    let dest = Number(line.split(" ")[1])

    nodes[src] = nodes[src] ? [...nodes[src], dest] : [dest]
    nodes[dest] = nodes[dest] ? [...nodes[dest], src] : [src]
  }

  if (rlcounter === 1) {
    let cornerNode = bfsMostDistantNode(1).index
    let path = bfsFindLongestPath(cornerNode)
    // console.log("Found Longest Path", path)

    let result
    if (path.length == N) {
      //console.log("Snake structure")
      result = snakeStructure(path)
    } else {
      //console.log("treeStructure")
      result = treeStructure(path)
    }

    console.log(`${result.pathLength}`)
    console.log(`${result.remove[0]} ${result.remove[1]}`)
    console.log(`${result.add[0]} ${result.add[1]}`)

    rl.close()
  }
})

function snakeStructure(path) {
  // Remove left corner node
  let lNode = path[0]
  path.shift()
  let rNode = path[0]
  let rMiddle = Math.floor(path.length / 2)
  rMiddle = path[rMiddle]

  //console.log("Remove ", lNode, rNode)
  nodes[lNode].splice(nodes[lNode].indexOf(rNode), 1)
  nodes[rNode].splice(nodes[rNode].indexOf(lNode), 1)

  //console.log("Add edge ", lNode, rMiddle)
  nodes[rMiddle].push(lNode)
  nodes[lNode].push(rMiddle)

  let cornerNode = bfsMostDistantNode(1).index
  let longestPath = bfsMostDistantNode(cornerNode).max

  return {
    pathLength: longestPath,
    remove: [rNode, lNode],
    add: [rMiddle, lNode]
  }
}

function treeStructure(path) {
  let rNode, lNode
  for (let i = 0; i < halfway(path); i++) {
    lNode = path[i]
    rNode = path[i + 1]
  }
  //console.log("Snip nodes", lNode, rNode)
  nodes[lNode].splice(nodes[lNode].indexOf(rNode), 1)
  nodes[rNode].splice(nodes[rNode].indexOf(lNode), 1)

  let lGroupCornerNode = bfsMostDistantNode(lNode).index
  let rGroupCornerNode = bfsMostDistantNode(rNode).index

  let lPath = bfsFindLongestPath(lGroupCornerNode)
  let rPath = bfsFindLongestPath(rGroupCornerNode)

  let lSnip, rSnip
  if (lPath.length === 2) {
    reSnipAtGivenPath(lPath, lNode, rNode)
    lSnip = 0
    rSnip = getMiddle(rPath, true)
  } else if (rPath.length === 2) {
    ;[lNode, rNode] = reSnipAtGivenPath(rPath, lNode, rNode)
    lSnip = getMiddle(lPath, false)
    rSnip = 0
  } else {
    // Normal case
    lSnip = getMiddle(lPath, false)
    rSnip = getMiddle(rPath, true)
  }

  //console.log("Add edge ", lPath[lSnip], rPath[rSnip])
  nodes[lPath[lSnip]].push(rPath[rSnip])
  nodes[rPath[rSnip]].push(lPath[lSnip])

  let cornerNode = bfsMostDistantNode(1).index
  let longestPath = bfsMostDistantNode(cornerNode).max

  return {
    pathLength: longestPath,
    remove: [rNode, lNode],
    add: [rPath[rSnip], lPath[lSnip]]
  }
}

/*
 * Return array length divided
 */
function halfway(path) {
  let halfway
  if (path.length % 2) {
    return Math.floor(path.length / 2)
  }
  return Math.ceil(path.length / 2)
}

/*
 * Re-add lNode && rNode
 * and snip at first index
 * in given path
 */
function reSnipAtGivenPath(thePath, lNode, rNode) {
  // Re-add
  nodes[lNode].push(rNode)
  nodes[rNode].push(lNode)

  lNode = thePath[0]
  rNode = thePath[1]
  // Remove
  nodes[thePath[0]].splice(nodes[thePath[0]].indexOf(thePath[1]), 1)
  nodes[thePath[1]].splice(nodes[thePath[1]].indexOf(thePath[0]), 1)

  return [lNode, rNode]
}

/*
 * Get the middle point of a fiven path
 * Alternate snippingpoint direction with boolean
 */
function getMiddle(groupPath, alternate) {
  let snippingPoint

  if (groupPath.length == 2) {
    snippingPoint = 1
  } else if (groupPath.length % 2) {
    snippingPoint = alternate
      ? Math.ceil((groupPath.length - 1) / 2)
      : Math.floor((groupPath.length - 1) / 2)
  } else {
    snippingPoint = alternate
      ? Math.floor((groupPath.length - 1) / 2)
      : Math.ceil((groupPath.length - 1) / 2)
  }
  return snippingPoint
}

/*
 *  BFS to find the most distant node from given start-node
 */
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
  distanceTo.forEach((element, idx) => {
    if (element > max) {
      max = element
      maxIndex = idx
    }
  })
  return { max: max, index: maxIndex }
}

/*
 * Same as bfsMostDistantNode but it returns a path
 */
function bfsFindLongestPath(start) {
  let visited = []
  for (let i = 1; i <= N; i++) {
    visited[i] = false
  }

  let q = []
  let path
  q.push([start])
  visited[start] = true

  while (q.length > 0) {
    path = q.shift()
    let dist = path.length

    let list = nodes[path[path.length - 1]]
    if (list) {
      for (let i = 0; i < list.length; i++) {
        let element = Number(list[i])
        if (visited[element] === true) continue

        visited[element] = true
        q.push([...path, element])
      }
    }
  }
  return path
}
