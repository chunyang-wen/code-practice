#!/bin/bash
set -e
DATE=$1
#ÒÆ¶¯
python gen_table_html.py data/domain_img_mobile.$DATE template/template_domain.html mail/domain_img_mobile_$DATE.html
python gen_table_html.py data/domain_img_txt_mobile.$DATE template/template_domain.html mail/domain_img_txt_mobile_$DATE.html
python gen_table_html.py data/domain_topic_1_mobile.$DATE template/template_domain.html mail/domain_topic_1_mobile_$DATE.html
python gen_table_html.py data/domain_txt_mobile.$DATE template/template_domain.html mail/domain_txt_mobile_$DATE.html
python gen_table_html.py data/his_mobile_image.$DATE template/template_his_mobile.html mail/his_mobile_image_$DATE.html
python gen_table_html.py data/his_mobile_image_txt.$DATE template/template_his_mobile.html mail/his_mobile_image_txt_$DATE.html
python gen_table_html.py data/his_mobile_topic_1.$DATE template/template_his_mobile.html mail/his_mobile_topic_1_$DATE.html
python gen_table_html.py data/his_mobile_topic_all.$DATE template/template_his_mobile.html mail/his_mobile_topic_all_$DATE.html
python gen_table_html.py data/his_mobile_txt.$DATE template/template_his_mobile.html mail/his_mobile_txt_$DATE.html
python gen_table_html.py data/his_mobile.$DATE template/template_his_mobile.html mail/his_mobile_$DATE.html
python gen_table_html.py data/his_mobile_daily template/template_his_daily_mobile.html mail/his_mobile_daily.html
python gen_table_html.py data/domain_topic_1_mobile_d2d_w2w.$DATE template/template_domain_d2d_w2w.html mail/domain_topic_1_d2d_w2w_$DATE.html
if [ ! -s data/his_mobile_topic_2.$DATE ]; then
    # empty touch zero
    echo -e "$DATE\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0" > data/his_mobile_topic_2.$DATE 
    echo -e "$DATE\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0" > data/domain_topic_2_mobile.$DATE 
fi
if [ ! -s data/his_mobile_topic_3.$DATE ]; then
    # empty touch zero
    echo -e "$DATE\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0" > data/his_mobile_topic_3.$DATE 
    echo -e "$DATE\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0\t0" > data/domain_topic_3_mobile.$DATE 
fi

python gen_table_html.py data/his_mobile_topic_2.$DATE template/template_his_mobile.html mail/his_mobile_topic_2_$DATE.html
python gen_table_html.py data/domain_topic_2_mobile.$DATE template/template_domain.html mail/domain_topic_2_mobile_$DATE.html
python gen_table_html.py data/his_mobile_topic_3.$DATE template/template_his_mobile.html mail/his_mobile_topic_3_$DATE.html
python gen_table_html.py data/domain_topic_3_mobile.$DATE template/template_domain.html mail/domain_topic_3_mobile_$DATE.html
python gen_table_html.py data/his_mobile_daily_wap_info template/template_his_daily_mobile.html mail/his_mobile_daily_wap_info.html

touch mail/merged.$DATE

python gen_mail_merged_html.py $DATE $DATE \
       mail/merged_rd.$DATE \
       template/template_merge_rd.html \
       mail/domain_img_mobile_$DATE.html \
       mail/domain_img_txt_mobile_$DATE.html \
       mail/domain_txt_mobile_$DATE.html \
       mail/domain_topic_1_mobile_$DATE.html \
       mail/his_mobile_image_$DATE.html \
       mail/his_mobile_image_txt_$DATE.html \
       mail/his_mobile_txt_$DATE.html \
       mail/his_mobile_topic_1_$DATE.html \
       mail/his_mobile_$DATE.html

python gen_mail_merged_html.py $DATE $DATE \
       mail/merged_ud.$DATE \
       template/template_merge_ud.html \
       mail/his_mobile_$DATE.html\
       mail/domain_img_mobile_$DATE.html \
       mail/domain_img_txt_mobile_$DATE.html \
       mail/domain_txt_mobile_$DATE.html \
       mail/his_mobile_daily.html

python gen_mail_merged_html.py $DATE $DATE \
       mail/merged_wap_info.$DATE \
       template/template_merge_wap_info.html \
       mail/his_mobile_daily_wap_info.html\
       mail/his_mobile_topic_all_$DATE.html\
       mail/domain_topic_1_mobile_$DATE.html \
       mail/his_mobile_topic_1_$DATE.html\
       mail/domain_topic_3_mobile_$DATE.html \
       mail/his_mobile_topic_3_$DATE.html\
       mail/domain_topic_2_mobile_$DATE.html \
       mail/his_mobile_topic_2_$DATE.html\
       mail/domain_topic_1_d2d_w2w_$DATE.html

cp mail/merged_rd.$DATE mail/mail_content_rd.html
cp mail/merged_ud.$DATE mail/mail_content_ud.html
cp mail/merged_wap_info.$DATE mail/mail_content_wap_info.html
#mail.conf.boss  mail.conf.self  mail.conf.ud 
if [[ $# == 1 ]] ;
then
    python gen_mail_text.py mail.conf.daily_rd
    cat mail/msg | /usr/sbin/sendmail -t

    python gen_mail_text.py mail.conf.daily_ud
    cat mail/msg | /usr/sbin/sendmail -t

    python gen_mail_text.py mail.conf.wap_info
    cat mail/msg | /usr/sbin/sendmail -t
else
    python gen_mail_text.py mail.conf.self
    cat mail/msg | /usr/sbin/sendmail -t
fi

