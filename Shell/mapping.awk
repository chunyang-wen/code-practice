BEGIN{
   FS=OFS="\t"; 
}
ARGIND==1{
    map[$1]=$2;
}
ARGIND==2{
    
    if(h){
        if($d in map){
            t = map[$d]
        }else{ 
            t ="无对应"
        }
        print t,$0;
    }else{
        if($d in map){
            $d = map[$d]
        }else{ 
            $d="无对应"
        }
        print;
    }
}
