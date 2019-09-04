
//
// Algebraic solution O(1) time
//

/*
 * Five by five matrix for remaining jumps 
*/
function knight_jumps_left(dx_, dy_, first_move) 
{
    let dx = Math.max(dx_, dy_);
    let dy = Math.min(dx_, dy_);

    switch(dx.toString() + "," + dy.toString()) {
        case "0,0": return 0; 
        case "1,0": return (first_move) ? 3 : 1;
        case "1,1": return 2;
        case "2,0": return 2;  
        case "2,1": return 1;
        case "2,2": return (first_move) ? 4 : 2;
        default: console.error("Wopsi");
    }
}

// JavaScript standard % operator is the Remainder 
// after devision and could therefore be negative.
// Implement mod operator which is always positive 
Number.prototype.mod = function(i) { 
    return ((this % i) + i) % i;
} 

function solve_algebraic_helper(dx_, dy_, dsx, dsy)
{
    let dx = Math.max(dx_, dy_);
    let dy = Math.min(dx_, dy_);


    if (dx <= 2) { return knight_jumps_left(dx, dy, true); }

    let ny = Math.max( Math.floor((2 * dy - dx -1) / 3), 0);
    let nx = Math.floor((dx - ny - 1) / 2);

    dx = dx - ( 2 * nx ) - ny;
    dy = (dy - ( 2 * ny ) - nx).mod(2);
    
    if (dsx > nx * 2 && dsy > ny * 1) {
        return nx + ny + knight_jumps_left(dx, dy, false);
    } else {
        return nx + ny + knight_jumps_left(dx, dy, true);
    }

}
    
function solve_algebraic(src_x, src_y, dest_x, dest_y, size_x, size_y)
{
    // Corner cases
    if (
        // Lower left corner
        src_x == 0 && src_y == 0 && dest_x == 1 && dest_y == 1 ||
        src_x == 1 && src_y == 1 && dest_x == 0 && dest_y == 0 ||
        // Upper right corner
        src_x == size_x -1 && src_y == size_y -1 && dest_x == size_x -2 && dest_y == size_y -2 ||
        src_x == size_x -2 && src_y == size_y -2 && dest_x == size_x -1 && dest_y == size_y -1 ||
        // Lower right corner
        src_x == size_x -1 && src_y == 0 && dest_x == size_x -2 && dest_y == 1 ||
        src_x == size_x -2 && src_y == 1 && dest_x == size_x -1 && dest_y == 0 ||
        // Upper left corner
        src_x == 0 && src_y == size_y -1 && dest_x == 1 && dest_y == size_y -2 ||
        src_x == 1 && src_y == size_y -2 && dest_x == 0 && dest_y == size_y -1
        ) 
        {
            return 4;
        }

    let deltax = Math.abs(src_x - dest_x);
    let deltay = Math.abs(src_y - dest_y);
    
    let dsx = Math.abs(src_x - size_x);
    let dsy = Math.abs(src_y - size_y);

    return solve_algebraic_helper(deltax, deltay, dsx, dsy);
}	



//
// Numeric solution with BFS, O(N_x * N_y)
//

function withinBounds( x, y, size_x, size_y) 
{ 
    if (x >= 0 && x <= (size_x -1) && y >= 0 && y <= (size_y -1))
        return true; 
    return false; 
} 

function bfs_minmum_jumps(src_x, src_y, dest_x, dest_y, size_x, size_y)
{
    if (src_x === dest_x && src_y === dest_y) {
        return 0;
    }

    // The 8 possible moves of a knight 
    const dx = [-2, -1,  1,  2, -2, -1, 1, 2]; 
    const dy = [-1, -2, -2, -1,  1,  2, 2, 1]; 

    let q = [];
    let map = {};

    q.push([src_x, src_y]);
    map[[src_x, src_y]] = 0;

    let x = 0;
    let y = 0;
    let searching = true;

    // loop untill we have one element in queue 
    while ( q.length > 0 )
    { 
        let coord = q.shift();

        // loop for all reachable states 
        for (let i = 0; i < dx.length; i++) 
        { 
            x = coord[0] + dx[i]; 
            y = coord[1] + dy[i]; 
  
            // If reachable state is not yet visited and 
            // inside board, push that state into queue 
            if (!withinBounds(x, y, size_x, size_y) || map[[x, y]] !== undefined) {
                continue;
            } else {
                q.push([x, y]);
                map[[x, y]] = map[coord] + 1;

                if ( x === dest_x && y === dest_y) {
                    return map[[x, y]];
                }
            } 
        } 
    }
    return "impossible";
}

const readline = require('readline')

const rl = readline.createInterface({
  //input: require('fs').createReadStream('sample.in'),
  input: process.stdin,
  output: process.stdout
})

let cnt = 0;
let size_x, size_y;
let x1, y1, x2, y2;
rl.on('line', (line) => {
    if (!line) { rl.close(); return; }

    if (cnt++ === 0) { /* Throw away first line */ 
        size_x = line.split(" ")[0]; size_y = line.split(" ")[1];
    }
    else if (cnt == 2) { 
        x1 = Number(line.split(" ")[0]); y1 = Number(line.split(" ")[1]);
    }
    else if (cnt == 3) {
        x2 = Number(line.split(" ")[0]); y2 = Number(line.split(" ")[1]);

        if (!true) {
            console.log(solve_algebraic(x1, y1, x2, y2, size_x, size_y));
        } else {
            console.log(bfs_minmum_jumps(x1, y1, x2, y2, size_x, size_y));
        }

        rl.close();
    }
});
