BEGIN{
    FS="\t";
    OFS="\t";   
}{
    #d for cols of index
    #f for start col num of content
    n=split(d,p," ");
    col = f;

    k=$(p[1]);
    for(i=2;i<=n;++i){
        k=k"\t"$(p[i]);    
    }

    keys[k]=1;

    for(i=col;i<=NF;++i){
        item[k"@"i]+=$i; 
    }

    num_filed = NF;
}END{
    for(i in keys){
        printf "%s",i;
        for(j=col;j<=num_filed;++j){
            printf  "\t%d",item[i"@"j];     
        }
        printf "\n";
    }   
}
