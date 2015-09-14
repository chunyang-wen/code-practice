BEGIN{
    FS=OFS="\t";
}ARGIND==1{
    dic[$d]=$0; 
}ARGIND==2{
    if($f in dic){
        print $0,dic[$f];    
    }else{
        print $0;
    }
}
