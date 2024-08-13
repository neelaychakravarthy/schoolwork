for file in file1.txt file2.txt file3.txt file4.txt
do
    echo "2 $file"
    time ./2 $file
    echo " "
done