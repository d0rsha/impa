
const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

let current = null;
rl.on('line', (line) => {
    if (current === null) {
        current = Number(line);
    } else {
        const target = Number(line);

        const c = (360 - current + target) % 360;
        const cc = (current + 360 - target) % 360;

        const result = (c <= cc) ? c : -cc;

        console.log(result);

        rl.close();
    }   
});


