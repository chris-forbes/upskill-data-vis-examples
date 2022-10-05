// Import the required file system library 'fs'
const fs = require("fs");

// relative path to the datafile we want to parse
const data_file = '../data/data_file.txt';

// Load our file
fs.readFile(data_file, 'utf-8', (err, file) => {
    // If there is some kind of error, print it and exit
    if (err) {
	console.log(err);
	process.exit(1);
    }

    // Holds our dataset
    let data_set = new Map();
    const lines = file.split('\n');

    // populate our data_set map
    for(let line of lines) {
	if(data_set.get(line)){
	    data_set.set(line, data_set.get(line) + 1);
	} else {
	    data_set.set(line, 1);
	}
    }
    
    // blank line at the end of the file
    data_set.delete('');
    // print our entire data set
    console.log(data_set);
    // print the max
    console.log([...data_set.entries()].reduce((a, e) => a[1] < e[1] ? e : a));
    // print the minimum
    console.log([...data_set.entries()].reduce((a, b) => a[1] > b[1] ? b : a));
    // calucate distrubtion percentages
    let sum = 0;
    data_set.forEach(value => {
	sum += value;
    });
    console.log("Total : " + sum);
    data_set.forEach((v, k) => {
	let percentage = (v / sum) * 100;
	console.log("Key: " + k + " Percentage: " + percentage + "%");
    });
});


