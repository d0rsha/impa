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

// Creed GeekForGeeks 
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


//function ulams_spine()
//{
    let x = OFFSET;
    let y = OFFSET;
    let dx = [-1,0,0,1];
    let dy = [0,-1,1,0];

    let to_num = Create2DArray(100);
    let to_coord = []; 

    to_num[x][y] = 1;
    to_coord[1] = [x,y];

    let dir = 0; // 0 = right, 1 = up, 2 = left, 3 = down
    let limit = 1; // Amount to prlet before changing direction
    let counter = 0; // How many printed in the current directio
    let turns = 0; // Counter for turns taken, every second; limit++

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
//    return [to_num, to_cord];
//}

for(let i = -5; i <= +5; i++) 
    {
        let row = "";
        for(let j = -5; j <= 5; j++) {
           if (to_num[i+OFFSET][j+OFFSET] != undefined) {
               row += to_num[i+OFFSET][j+OFFSET] + "\t";
           }
           else {
               row += " X " + "\t";
           }
        }
        console.log(row);
    }


let _case = 1;
let src, dest;
let reads = 0;
rl.on('line', (line) => {
    if (!line) { rl.close(); return }

    if (reads++ === 0) {
        src = Number(line);
    } else {
        dest = Number(line);
        let bfs_map = {};
        let bfs_q = [];

        
        bfs_q.push(to_coord[src]);
        bfs_map[(to_coord[src])] = 0;

        //
        // Breadth First Search (BFS)
        //
        while(bfs_q.length > 0) {
            // Skip if src || dest not reachable (TODO: Should not be in for loop!)
            if (isPrime(src) || isPrime(dest)) { 
                console.log("Not prime");
                break;
            }  

            // console.log("Queue Size: ", bfs_q.length);
            // console.log("Map: ", bfs_map)
            const curr = bfs_q.shift();

            for(let i = 0; i < 4; i++) {
                
                // let next = curr;
                const nextx = curr[0] + Number(dx[i]);
                const nexty = curr[1] + Number(dy[i]);
                // const nextx = curr[0];
                // const nexty = curr[1];

                //next[0] += Number(dx[i]);
                //next[1] += Number(dy[i]);

                // Check if path is possible 
                if(to_num[nextx][nexty] === undefined) {
                    continue;
                }
                // Check if there already exists shorter path to coordinate
                else if(bfs_map[([nextx,nexty])] !== undefined) {
                    continue;
                }
                bfs_map[([nextx,nexty])] = Number(bfs_map[(curr)]) + 1; 
                bfs_q.push([nextx,nexty]);

                if (nextx > 100 || nexty > 100) {
                    console.error("Out of bounds");
                }
                else if (to_num[nextx][nexty] === dest) {
                    console.log("Found exit from ", src, " to ", to_num[nextx][nexty]);
                    bfs_q = [];
                }
            }
        }

        console.log("to_coord[dest]", to_coord[dest]);
        console.log("bfs_map[coord]", bfs_map[to_coord[dest]]);


        // If dest is not inside map then no path available
        if(!bfs_map[to_coord[dest]] || src == dest) {
            console.log("Case ", _case++, ": impossible");
        } else {
            console.log("Case ", _case++, ": ", bfs_map[to_coord[dest]]);
        }

        reads = 0;
    }

    
});


