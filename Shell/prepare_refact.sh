# prepare data
# domain^temp^tu^l2_to pv1 pv2 click gain
# l2_to = 1 mid-page
# l2_to = 2 zhixin
# l2_to = 3 ps

if [ $# -gt 0 ]
then
    DATE=$1
else
    DATE=`date -d "1 days ago" +%Y%m%d`
fi

# replace ^ with \t
sed 's/\^/\t/g' download/base_mobile.$DATE >temp_dir/base_mobile.$DATE

# $4 represents daoliu
# drop tu list
awk -F"\t" -v OFS="\t" -f awks/split_temp.awk temp_dir/base_mobile.$DATE > temp_dir/base_mobile_ps.$DATE

# sum key value
# domain temp tu pv1 pv2 click gain l2to
#python ~/tools/key_value_sum.py -f mobile_ps.conf < temp_dir/base_mobile_ps.$DATE > temp_dir/base_mobile_ps_sum.$DATE

# split to each template
# template level: NP/NPS
# after sum: domain temp pv1 pv2 click gain lu2to l2to_sum
awk -F"\t" '$2~/ad_txt/' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_txt.$DATE

awk -F"\t" '$2~/ad_image_txt/' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_image_txt.$DATE
awk -F"\t" '$2~/ad_image/ && $2 !~/ad_image_txt/' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_image.$DATE

awk -F"\t" '$2~/ad_topic_1/' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_topic_1.$DATE

# all image topic currently not in working
awk -F"\t" '$2~/ad_topic_2/' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_topic_2.$DATE

awk -F"\t" '$2~/ad_topic_3/' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_topic_3.$DATE

awk -F"\t" '$2~/ad_topic_/' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_topic_all_tmp.$DATE


# domain template level: 
# temp_dir/base_mobile_ps.$DATE is domain template level
# all level: 
awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print $1,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps1.conf \
> temp_dir/base_mobile_ps_ad_domain_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps_ad_txt.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps2.conf \
> temp_dir/base_mobile_ps_ad_txt_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps_ad_image_txt.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps2.conf \
> temp_dir/base_mobile_ps_ad_image_txt_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps_ad_image.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps2.conf \
> temp_dir/base_mobile_ps_ad_image_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps_ad_topic_1.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps2.conf \
> temp_dir/base_mobile_ps_ad_topic_1_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps_ad_topic_2.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps2.conf \
> temp_dir/base_mobile_ps_ad_topic_2_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps_ad_topic_3.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps2.conf \
> temp_dir/base_mobile_ps_ad_topic_3_all.$DATE

awk -F"\t" -v OFS="\t" -v date=$DATE -v shit="SHIT" \
'{print date,shit,$3,$4,$5,$6,$7,$8}' temp_dir/base_mobile_ps_ad_topic_all_tmp.$DATE |\
python ~/tools/key_value_sum.py -f mobile_ps2.conf \
> temp_dir/base_mobile_ps_ad_topic_all.$DATE


# reformat value's position
# domain temp tu pv1 pv2 click gain PS/NPS_num sum
awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_txt.$DATE > temp_dir/domain_ps_percentage_ad_txt.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_image.$DATE > temp_dir/domain_ps_percentage_ad_image.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_image_txt.$DATE > temp_dir/domain_ps_percentage_ad_image_txt.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_topic_1.$DATE > temp_dir/domain_ps_percentage_ad_topic_1.$DATE
awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_topic_2.$DATE > temp_dir/domain_ps_percentage_ad_topic_2.$DATE
awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_topic_3.$DATE > temp_dir/domain_ps_percentage_ad_topic_3.$DATE
awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_topic_all.$DATE > temp_dir/domain_ps_percentage_ad_topic_all.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_all.$DATE > temp_dir/domain_ps_percentage_ad_all.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_txt_all.$DATE > temp_dir/domain_ps_percentage_ad_txt_all.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_image_txt_all.$DATE > temp_dir/domain_ps_percentage_ad_image_txt_all.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_image_all.$DATE > temp_dir/domain_ps_percentage_ad_image_all.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_domain_all.$DATE > temp_dir/domain_ps_percentage_ad_domain_all.$DATE

awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_topic_1_all.$DATE > temp_dir/domain_ps_percentage_ad_topic_1_all.$DATE
awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_topic_2_all.$DATE > temp_dir/domain_ps_percentage_ad_topic_2_all.$DATE
awk -F"\t" -v OFS="\t" -f awks/diversion.awk temp_dir/base_mobile_ps_ad_topic_3_all.$DATE > temp_dir/domain_ps_percentage_ad_topic_3_all.$DATE


# domain temp PS/NPS pv1 pv2 click gain PS/NPS-percentage
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_image.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_image.$DATE
# domain temp PS/NPS pv1 pv2 click gain PS/NPS-percentage
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_image_txt.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_image_txt.$DATE
# domain temp PS/NPS pv1 pv2 click gain PS/NPS-percentage
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_txt.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_txt.$DATE
# domain temp PS/NPS pv1 pv2 click gain PS/NPS-percentage
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_topic_1.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_topic_1.$DATE
# domain temp PS/NPS pv1 pv2 click gain PS/NPS-percentage
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_topic_2.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_topic_2.$DATE
# domain temp PS/NPS pv1 pv2 click gain PS/NPS-percentage
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_topic_3.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_topic_3.$DATE

#python ~/tools/key_value_append.py -f mobile_ps_appedn.conf \

python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_txt_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_txt_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_image_txt_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_image_txt_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_image_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_image_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_topic_1_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_topic_1_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_topic_2_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_topic_2_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_topic_3_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_topic_3_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_topic_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_topic_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_all.$DATE
python ~/tools/key_value_sum.py -f mobile_ps_per.conf < temp_dir/base_mobile_ps_ad_domain_all.$DATE |\
sort -k2nr,2 > temp_dir/base_mobile_sum_ad_domain_all.$DATE

# no need to aggregrate
cat temp_dir/base_mobile_sum_ad_image_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_image_all.$DATE
cat temp_dir/base_mobile_sum_ad_txt_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_txt_all.$DATE
cat temp_dir/base_mobile_sum_ad_image_txt_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_image_txt_all.$DATE
cat temp_dir/base_mobile_sum_ad_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_all.$DATE
cat temp_dir/base_mobile_sum_ad_domain_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_domain_all.$DATE
cat temp_dir/base_mobile_sum_ad_topic_1_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_topic_1_all.$DATE
cat temp_dir/base_mobile_sum_ad_topic_2_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_topic_2_all.$DATE
cat temp_dir/base_mobile_sum_ad_topic_3_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_topic_3_all.$DATE
cat temp_dir/base_mobile_sum_ad_topic_all.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_topic_all.$DATE


# aggregrate small pvs
# domain temp PS/NPS pv1 pv2 click gain PS/NPS-percentage
awk -F"\t" -v OFS="\t" -f awks/aggregate_small_pvs.awk temp_dir/base_mobile_sum_ad_txt.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_txt.$DATE

awk -F"\t" -v OFS="\t" -f awks/aggregate_small_pvs.awk temp_dir/base_mobile_sum_ad_topic_1.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_topic_1.$DATE

awk -F"\t" -v OFS="\t" -f awks/aggregate_small_pvs.awk temp_dir/base_mobile_sum_ad_topic_2.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_topic_2.$DATE

awk -F"\t" -v OFS="\t" -f awks/aggregate_small_pvs.awk temp_dir/base_mobile_sum_ad_topic_3.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_topic_3.$DATE

awk -F"\t" -v OFS="\t" -f awks/aggregate_small_pvs.awk temp_dir/base_mobile_sum_ad_image_txt.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_image_txt.$DATE

awk -F"\t" -v OFS="\t" -f awks/aggregate_small_pvs.awk temp_dir/base_mobile_sum_ad_image.$DATE |\
python ~/tools/key_value_append.py -f append.conf > temp_dir/base_mobile_sum_AS_ad_image.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_image_txt.$DATE temp_dir/base_mobile_sum_AS_ad_image_txt.$DATE \
> data/domain_img_txt_mobile.$DATE
#    print $0,a[$1]*100,$3*a[$1], $3*a[$1]/$2*100;
#    printf "%s\t%.4f\t%.0f\t%.4f\n" """"$0,a[$1]*100,$3*a[$1], $3*a[$1]/$2*100;

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_topic_1.$DATE temp_dir/base_mobile_sum_AS_ad_topic_1.$DATE \
> data/domain_topic_1_mobile.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_topic_2.$DATE temp_dir/base_mobile_sum_AS_ad_topic_2.$DATE \
> data/domain_topic_2_mobile.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_topic_3.$DATE temp_dir/base_mobile_sum_AS_ad_topic_3.$DATE \
> data/domain_topic_3_mobile.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_txt.$DATE temp_dir/base_mobile_sum_AS_ad_txt.$DATE \
> data/domain_txt_mobile.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_image.$DATE temp_dir/base_mobile_sum_AS_ad_image.$DATE \
> data/domain_img_mobile.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_domain_all.$DATE temp_dir/base_mobile_sum_AS_ad_domain_all.$DATE \
> data/domain_total.$DATE


# output format
# domain temp pv1 pv2 click gain s1ctr s2ctr ctr s2cpm cpm acp daoliu
# history info

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_image_all.$DATE temp_dir/base_mobile_sum_AS_ad_image_all.$DATE \
>> data/his_mobile_image

cat data/his_mobile_image |sort |uniq |tail -n 14 > data/his_mobile_image.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_txt_all.$DATE temp_dir/base_mobile_sum_AS_ad_txt_all.$DATE \
>> data/his_mobile_txt


cat data/his_mobile_txt |sort |uniq |tail -n 14 > data/his_mobile_txt.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_image_txt_all.$DATE temp_dir/base_mobile_sum_AS_ad_image_txt_all.$DATE \
>> data/his_mobile_image_txt

cat data/his_mobile_image_txt |sort |uniq |tail -n 14 > data/his_mobile_image_txt.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_all.$DATE temp_dir/base_mobile_sum_AS_ad_all.$DATE \
>> data/his_mobile

cat data/his_mobile |sort |uniq |tail -n 14 > data/his_mobile.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_topic_1_all.$DATE temp_dir/base_mobile_sum_AS_ad_topic_1_all.$DATE \
>> data/his_mobile_topic_1

cat data/his_mobile_topic_1 |sort |uniq |tail -n 14 > data/his_mobile_topic_1.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_topic_2_all.$DATE temp_dir/base_mobile_sum_AS_ad_topic_2_all.$DATE \
>> data/his_mobile_topic_2

cat data/his_mobile_topic_2 |sort |uniq |tail -n 14 | sed '/^$/d'> data/his_mobile_topic_2.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_topic_3_all.$DATE temp_dir/base_mobile_sum_AS_ad_topic_3_all.$DATE \
>> data/his_mobile_topic_3

cat data/his_mobile_topic_3 |sort |uniq |tail -n 14 > data/his_mobile_topic_3.$DATE

awk -F"\t" -v OFS="\t" -f awks/append_diversion.awk temp_dir/domain_ps_percentage_ad_topic_all.$DATE temp_dir/base_mobile_sum_AS_ad_topic_all.$DATE \
>> data/his_mobile_topic_all

cat data/his_mobile_topic_all |sort |uniq |tail -n 14 > data/his_mobile_topic_all.$DATE



# single daily history
tail -1 data/his_mobile_image | sed "s/$DATE/图片/1" > data/his_mobile_daily
tail -1 data/his_mobile_image_txt | sed "s/$DATE/图文/1">> data/his_mobile_daily
tail -1 data/his_mobile_txt | sed "s/$DATE/文本/1" >> data/his_mobile_daily
#tail -1 data/his_mobile_topic_1 | sed "s/$DATE/信息流/1" >> data/his_mobile_daily

# single daily history for wap info flow
tail -1 data/his_mobile_topic_1 | sed "s/$DATE/图文信息流/1" > data/his_mobile_daily_wap_info
tail -1 data/his_mobile_topic_2 | sed "s/$DATE/图片信息流/1" | grep -F "图片" >> data/his_mobile_daily_wap_info
tail -1 data/his_mobile_topic_3 | sed "s/$DATE/文本信息流/1" >> data/his_mobile_daily_wap_info
tail -1 data/his_mobile_topic_all | sed "s/$DATE/信息流总和/" >> data/his_mobile_daily_wap_info

sh gen_tu.sh $DATE
