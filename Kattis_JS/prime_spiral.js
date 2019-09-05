const OFFSET = 50
const ROOF   = 10000

const readline = require('readline')

const rl = readline.createInterface({
  // input: require('fs').createReadStream('sample.in'),
  input: process.stdin,
  output: process.stdout
})

function Create2DArray(rows) {
    var arr = [];
    for (var i=0;i<rows;i++) {
       arr[i] = [];
    }
  
    return arr;
}

function isPrime(n) 
{ 
	// Corner case 
	if (n <= 1) 
		return false; 
	// Check from 2 to n-1 
	for (let i = 2; i < n; i++) 
		if (n % i == 0) 
			return false; 

	return true; 
} 

function int(arr)
{
    return Number(arr[1]) * 100 + Number(arr[0]);
}


// construct_ulams_spine() {
let x = OFFSET;
let y = OFFSET;
let dx = [-1,0,0,1];
let dy = [0,-1,1,0];

let to_num = Create2DArray(100);
let to_coord = []; 

to_num[x][y] = 1;
to_coord[1] = [x,y];

let dir = 0;        // 0 = right, 1 = up, 2 = left, 3 = down
let limit = 1;      // Amount to prlet before changing direction
let counter = 0;    // How many printed in the current directio
let turns = 0;      // Counter for turns taken, every second; limit++

for (let i = 1; i < ROOF; i++) {
    //  Skip if Prime number
    if(isPrime(i)) {
        ;
    }
    //  Add if Composite number
    else {
        to_num[x][y] = i;
        to_coord[i] = [x,y];
    }

    switch(dir) {
        case 0: y++; break;
        case 1: x--; break;
        case 2: y--; break;
        case 3: x++; break;
    }
    
    counter++;

    if (counter >= limit) {
        counter = 0;
        turns = (turns + 1) % 2;
        dir = (dir + 1) % 4;
        
        if (turns == 0) {
            limit++;
        }
    }
}

let _case = 1;
let src, dest;
rl.on('line', (line) => {
    if (!line) { rl.close(); return }

    src = Number(line.split(" ")[0]);
    dest = Number(line.split(" ")[1]);
    let bfs_map = {};
    let bfs_q = [];
    let run = true;


    // Skip if src || dest not reachable
    if ((src == dest) || (isPrime(src) || isPrime(dest))) { 
        run = false;
    } else {
        bfs_q.push([to_coord[src][0], to_coord[src][1]]);
        bfs_map[(to_coord[src])] = 0;
    } 

    //
    // Breadth First Search (BFS)
    //
    while(bfs_q.length > 0 && run) {
        const curr = bfs_q.shift();

        for(let i = 0; i < 4; i++) {
            const nextx = curr[0] + Number(dx[i]);
            const nexty = curr[1] + Number(dy[i]);

            // Check if path is possible 
            if(nextx > 99 || nextx < 0 ||nexty > 99 || nexty < 0) {
                continue;
            }
            
            if(to_num[nextx][nexty] === undefined) {
                continue;
            }
            // Check if there already exists shorter path to coordinate
            else if(bfs_map[([nextx,nexty])] !== undefined) {
                continue;
            }
            bfs_map[([nextx,nexty])] = Number(bfs_map[(curr)]) + 1; 
            bfs_q.push([nextx,nexty]);

            // With BFS the first occourance must also be shortest 
            if (to_num[nextx][nexty] === dest) {
                run = false;
            }
        }
    }

    
    // If dest is not inside map then no path available
    if ( src == dest ||  (isPrime(src) || isPrime(dest))) {
        console.log("Case", (_case++).toString(10) +  ": impossible");
    } else if(bfs_map[to_coord[dest]] === undefined) {
        console.log("Case", (_case++).toString(10) + ": impossible");
    } else {
        console.log("Case", (_case++).toString(10) + ":", bfs_map[to_coord[dest]]);
    }

});