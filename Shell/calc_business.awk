BEGIN{
    FS=OFS="\t";
    k=d;
}{
    n=split(d,p," ");
    k=$(p[1]);
    for(i=2;i<=n;++i){
        k=k"\t"$(p[i]);    
    }
    s=f;
    pv1[k]+=$(s++);
    pv2[k]+=$(s++);
    click[k]+=$(s++);
    gain[k]+=$(s++);
    pv2d[k]+=$(s++);
}function calc(){

}END{
    for(i in pv1){
        if(pv1[i]>0){
            s1_ctr = 1000*pv2[i]/pv1[i];
            ctr = 1000*click[i]/pv1[i];
            cpm = 1000*gain[i]/pv1[i];
        }else{
            s1_ctr = 0;
            ctr = 0;
            cpm = 0;
        }
        if(pv2[i]>0){
            s2_ctr = 1000*click[i]/pv2[i];
            s2_cpm = 1000*gain[i]/pv2[i];
            dl = 100*pv2d[i]/pv2[i];
        }else{
            s2_ctr = 0;
            s2_cpm = 0;
            dl = 0;
        }
        if(click[i]>0){
            acp = gain[i]/click[i];
        }else{
            acp = 0;
        }

        print i,\
        pv1[i],\
        pv2[i],\
        click[i],\
        gain[i],\
        s1_ctr,\
        s2_ctr,\
        ctr,\
        s2_cpm,\
        cpm,\
        acp,\
        dl;
    }
}
