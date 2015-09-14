# we assume, temp is in the second place
# xx^temp^xx
BEGIN{
    FS="^";
    temp[1]="template_inlay_all_mobile_lu";
    file[1]="../lu_temp/download/base_mobile."""DATE;
    temp[2]="template_inlay_all_mobile_lu_native";
    file[2]="../propose_ad/download/base_mobile."""DATE;
    temp[3]="baiduTlinkNeiwen_mob";
    file[3]="../intext/download/base_mobile."""DATE;
}
{

    for(ind in temp) {
        #print temp[ind],file[ind]
        if(match($2,temp[ind]) != 0) {print $0 > file[ind];}
    }
}
