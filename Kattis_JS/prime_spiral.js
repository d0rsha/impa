const readline = require('readline')

const rl = readline.createInterface({
  // input: require('fs').createReadStream('sample.in'),
  input: process.stdin,
  output: process.stdout
})

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

//function ulams_spine()
//{
    let x = 0;
    let y = 0;
    let dx = [-1,0,0,1];
    let dy = [0,-1,1,0];

    let to_num = [];
    let to_coord = []; 

    to_num[{x,y}] = 1;
    to_coord[1] = {x,y};

    let dir = 0; // 0 = right, 1 = up, 2 = left, 3 = down
    let limit = 1; // Amount to prlet before changing direction
    let counter = 0; // How many printed in the current directio
    let turns = 0; // Counter for turns taken, every second; limit++

    for (let i = 1; i < 10000; i++) {
        //  Skip if Prime number
        if(isPrime(i)) {
            ;
        }
        //  Add if Composite number
        else {
            to_num[{x,y}] = i;
            to_coord[i] = {x,y};
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

for(let i = -12; i <= 12; i++) 
    {
        let row = "";
        for(let j = -12; j <= 12; j++) {
           if (to_num[{i,j}] ) {
               row += to_num[{i,j}] + "\t";
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
        bfs_map;
        bfs_q;

        
        bfs_q.push(to_coord[src]);

        //
        // Breadth First Search (BFS)
        //
        while(!bfs_q.empty()) {
            // Skip if src || dest not reachable
            if (isPrime(src) || isPrime(dest)) { 
                break;
            } 

            let curr = bfs_q.shift();
            

            for(let i = 0; i < 4; i++) {
                let next = curr;
                
                next.first += dx[i];
                next.second += dy[i];

                // Check if path is possible 
                if(!to_num.count(next)) {
                    continue;
                }
                // Check if there already exists shorter path to coordinate
                else if(bfs_map.next)) {
                    continue;
                }
                bfs_map[next] = bfs_map[curr] + 1;
                bfs_q.push(next);
            }
        }
        // If dest is not inside map then no path available
        if(!bfs_map.count(to_coord[dest]) || src == dest) {
            console.log("Case ", _case, ": impossible");
        } else {
            console.log("Case ", _case, ": ", bfs_map[to_coord[dest]]);
        }

        reads = 0;
    }

    
});


