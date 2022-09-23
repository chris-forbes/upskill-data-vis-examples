use clap::Parser;
use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;
use std::collections::HashMap;

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
struct Args {
    #[clap(short, long, value_parser)]
    file_path: String
}


fn main() {
    let args = Args::parse();
    println!("Reading file {}!", args.file_path);
    println!("{}","=".repeat(100));
    // Read the file line by line to a new Vector
    let mut data: Vec<String> = Vec::new();
    if let Ok(lines) = read_lines(args.file_path) {
        for line in lines {
            if let Ok(value) = line {
                data.push(value);
            }
        }
    }
    // determine all the counts of the input data file
    if let Ok(value_sums) = count_duplicates(&data) {
        println!("Total counts:");
        println!("{}","=".repeat(100));
        for(k, v) in &value_sums {
            println!("Word: {}\t Count: {}", k, v);
        }

        println!("\nOverall distribution");
        println!("{}","=".repeat(100));
        let total = get_total(&value_sums);
        for(k, v) in &value_sums {
            let distribution: f32 = (*v as f32/ total as f32) * (100.00) as f32;
            println!("Word: {}\t percentage of total: {}%", k, distribution);
        }
        println!("{}","=".repeat(100));
        println!("Min & Max");
        println!("{}","=".repeat(100));
        let max = value_sums.iter().max_by(|a, b| a.1.cmp(&b.1)).map(|(k, _v)| k).unwrap();
        let min = value_sums.iter().min_by(|a, b| a.1.cmp(&b.1)).map(|(k, _v)| k).unwrap();
        println!("Word: {}\t Max: {}", max, value_sums[max]);
        println!("Word: {}\t Min: {}", min, value_sums[min]);
    }

    
}

fn get_total<'a>(data_set: &'a HashMap<&'a String, i32>) ->i32{
    // let mut data: HashMap<&String, f64> = HashMap::new();
    // let mut sum_of_all: i32 = 0;
    let total = data_set.values().cloned().map(|x| x as i32).sum();
    println!("Total:{}", total);
    total
}

fn count_duplicates(values: &Vec<String>) -> io::Result<HashMap<&String, i32>>{
    let mut value_dict: HashMap<&String, i32> = HashMap::new();
    for v in values {
        *value_dict.entry(v).or_insert(1) += 1;
    }
    Ok(value_dict)
}

fn read_lines<P> (filename: P) -> io::Result<io::Lines<io::BufReader<File>>> where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
