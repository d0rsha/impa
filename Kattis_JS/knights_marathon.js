// The 8 possible moves of a knight
const jumpx = [-2, -1, 1, 2, -2, -1, 1, 2]
const jumpy = [-1, -2, -2, -1, 1, 2, 2, 1]

// Locie variables
let x = 0
let y = 0
let cnt = 0
let size_x, size_y
let x1, y1, x2, y2

//
// Algebraic solution O(1) time
//
function knight_jumps_left(dx_, dy_, first_move) {
  let dx = Math.max(dx_, dy_)
  let dy = Math.min(dx_, dy_)

  switch (dx.toString() + "," + dy.toString()) {
    case "0,0":
      return 0
    case "1,0":
      return first_move ? 3 : 1
    case "1,1":
      return 2
    case "2,0":
      return 2
    case "2,1":
      return 1
    case "2,2":
      return first_move ? 4 : 2
    default:
      console.error("Wopsi")
  }
}

// JavaScript standard % operator is the Remainder
// after devision and could therefore be negative.
// Implement mod operator which is always positive
Number.prototype.mod = function(i) {
  return ((this % i) + i) % i
}

function solve_algebraic_helper(dx_, dy_, dsx, dsy) {
  let dx = Math.max(dx_, dy_)
  let dy = Math.min(dx_, dy_)

  // within range
  if (dx <= 2) {
    return knight_jumps_left(dx, dy, true)
  }

  // calculate n_y and n_x after formula
  let ny = Math.max(Math.floor((2 * dy - dx - 1) / 3), 0)
  let nx = Math.floor((dx - ny - 1) / 2)

  dx = dx - 2 * nx - ny
  dy = (dy - 2 * ny - nx).mod(2)

  // If destionation is just along a border
  if (dsx > nx * 2 && dsy > ny * 1) {
    return nx + ny + knight_jumps_left(dx, dy, false)
  } else {
    return nx + ny + knight_jumps_left(dx, dy, true)
  }
}

function solve_algebraic(src_x, src_y, dest_x, dest_y, size_x, size_y) {
  // Declare all corner cases
  if (
    // Lower left corner
    (src_x == 0 && src_y == 0 && dest_x == 1 && dest_y == 1) ||
    (src_x == 1 && src_y == 1 && dest_x == 0 && dest_y == 0) ||
    // Upper right corner
    (src_x == size_x - 1 &&
      src_y == size_y - 1 &&
      dest_x == size_x - 2 &&
      dest_y == size_y - 2) ||
    (src_x == size_x - 2 &&
      src_y == size_y - 2 &&
      dest_x == size_x - 1 &&
      dest_y == size_y - 1) ||
    // Lower right corner
    (src_x == size_x - 1 &&
      src_y == 0 &&
      dest_x == size_x - 2 &&
      dest_y == 1) ||
    (src_x == size_x - 2 &&
      src_y == 1 &&
      dest_x == size_x - 1 &&
      dest_y == 0) ||
    // Upper left corner
    (src_x == 0 &&
      src_y == size_y - 1 &&
      dest_x == 1 &&
      dest_y == size_y - 2) ||
    (src_x == 1 && src_y == size_y - 2 && dest_x == 0 && dest_y == size_y - 1)
  ) {
    return 4
  }

  let dx = Math.abs(src_x - dest_x)
  let dy = Math.abs(src_y - dest_y)

  let dsx = Math.abs(src_x - size_x)
  let dsy = Math.abs(src_y - size_y)

  return solve_algebraic_helper(dx, dy, dsx, dsy)
}

//
// Numeric solution with BFS, O(N_x * N_y)
//

function withinBounds(x, y, size_x, size_y) {
  if (x >= 0 && x <= size_x - 1 && y >= 0 && y <= size_y - 1) return true
  return false
}

function bfs_minmum_jumps(src_x, src_y, dest_x, dest_y, size_x, size_y) {
  if (src_x === dest_x && src_y === dest_y) {
    return 0
  }

  let q = []
  let map = {}

  q.push([src_x, src_y])
  map[[src_x, src_y]] = 0

  // Loop until queue is empty or function returns
  while (q.length > 0) {
    let coord = q.shift()

    // loop for all reachable states
    for (let i = 0; i < jumpx.length; i++) {
      x = coord[0] + jumpx[i]
      y = coord[1] + jumpy[i]

      // If reachable state is not yet visited and
      // inside board, push that state into queue
      if (!withinBounds(x, y, size_x, size_y) || map[[x, y]] !== undefined) {
        continue
      } else {
        q.push([x, y])
        map[[x, y]] = map[coord] + 1

        // we have reached our destination, yeey!
        if (x === dest_x && y === dest_y) {
          return map[[x, y]]
        }
      }
    }
  }
  return Infinity
}

const readline = require("readline")

const rl = readline.createInterface({
  //input: require('fs').createReadStream('sample.in'),
  input: process.stdin,
  output: process.stdout
})

rl.on("line", line => {
  if (!line) {
    rl.close()
    return
  }

  if (cnt++ === 0) {
    size_x = line.split(" ")[0]
    size_y = line.split(" ")[1]
  } else if (cnt == 2) {
    x1 = Number(line.split(" ")[0])
    y1 = Number(line.split(" ")[1])
  } else if (cnt == 3) {
    x2 = Number(line.split(" ")[0])
    y2 = Number(line.split(" ")[1])

    // Choose BFS
    if (size_x < 10 && size_y < 10) {
      console.log(bfs_minmum_jumps(x1, y1, x2, y2, size_x, size_y))
    }
    // Choose Math forumla
    else {
      if (x1 == x2 && y1 == y2) {
        console.log(0)
        return
      }

      // Problem when destination is corner case.
      // Solution: Move dest 1 step in each dir,
      //           solve for each case, pick optimal case

      const end = [x2, y2]
      let coord
      let q = []

      // loop for all reachable states
      for (let i = 0; i < jumpx.length; i++) {
        x = end[0] + jumpx[i]
        y = end[1] + jumpy[i]

        if (withinBounds(x, y, size_x, size_y)) {
          q.push(solve_algebraic(x1, y1, x, y, size_x, size_y) + 1)
        }
      }

      //console.log(q);

      // Pick best case
      let best = q.shift()
      for (let i = 0; i < q.length; ) {
        let cand = q.shift()

        if (cand < best) {
          best = cand
        }
      }
      console.log(best)
    }

    rl.close()
  }
})
