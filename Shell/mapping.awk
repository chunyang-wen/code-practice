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
            t ="�޶�Ӧ"
        }
        print t,$0;
    }else{
        if($d in map){
            $d = map[$d]
        }else{ 
            $d="�޶�Ӧ"
        }
        print;
    }
}
