

load_data_file <- function(fileName) {
        file_handle <- file(fileName, open="r")
        data <- readLines(file_handle)
        close(file_handle)
        rm(file_handle)
        return(data)
}

count_duplicates <- function(data) {
        unique_values <- unique(data)
        df <- data.frame()
        for(row in unique_values) {
                df <- rbind(df, data.frame(str=row, count=length(grep(row, data))))
        }
        return(df)
}

determine_distribution <- function(data, total, names) {
        df <- data.frame()
        for(row in names) {
                row_val = data[which(data$str == row),]
                counter <- (row_val[,'count'] / total) * 100    
                df <- rbind(df, data.frame(str=row, count = row_val[,'count'], distrib = counter))
        }
        return(df)
}

main <- function() {
        print("Loading data_file.txt")  
        data <- load_data_file("data_file.txt")
        count_totals <- count_duplicates(data)
        total <- sum(count_totals[, 'count'])
        distribution <- determine_distribution(count_totals, total, unique(data))
        #
        # Print out result set
        #
        print("Data spread:")
        print(distribution)
        print("Max Value:")
        print(count_totals[which.max(count_totals$count),])
        print("Min Value:")
        print(count_totals[which.min(count_totals$count),])

}

main()

