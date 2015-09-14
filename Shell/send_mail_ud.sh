#!/bin/bash
DATE=$1
python gen_table_html.py data/domain_with_business.$DATE template/template_domain_business.html mail/domain_with_business_$DATE.html
python gen_table_html.py data/his.$DATE           template/template_his.html mail/his_$DATE.html
python gen_table_html.py data/temp.$DATE          template/template_domain.html mail/temp_$DATE.html
python gen_table_html.py data/domain_imgtxt_with_product.$DATE template/template_domain_with_product.html mail/domain_imgtxt_p_$DATE.html
python gen_table_html.py data/domain_img_with_product.$DATE    template/template_domain_with_product.html mail/domain_img_p_$DATE.html
python gen_table_html.py data/domain_txt_with_product.$DATE    template/template_domain_with_product.html mail/domain_txt_p_$DATE.html
python gen_table_html.py data/product.$DATE       template/template_domain.html mail/product_$DATE.html
#python gen_table_html.py data/delta_2day.$DATE    template/template_delta_2.html mail/delta_2day_$DATE.html
#python gen_table_html.py data/delta_7day.$DATE template/template_delta_2.html mail/delta_7day_$DATE.html

touch mail/merged.$DATE

python gen_mail_merged_html.py $DATE $DATE \
       mail/merged.$DATE \
       template/template_merge_ud.html \
       mail/his_$DATE.html  \
       mail/domain_with_business_$DATE.html \
       mail/temp_$DATE.html \
       mail/domain_img_p_$DATE.html \
       mail/domain_imgtxt_p_$DATE.html \
       mail/domain_txt_p_$DATE.html \
       mail/product_$DATE.html  
       #mail/delta_2day_$DATE.html \
       #mail/delta_7day_$DATE.html

cp mail/merged.$DATE mail/mail_content.html
cp data/attach/$DATE/* mail/
#cp mail/mail_content.html mail/propose_ad_data
if [[ $# == 1 ]] ;
then
    python gen_mail_text_2.py mail.conf.ud
else
    python gen_mail_text_2.py mail.conf.self
fi

cat mail/msg | /usr/sbin/sendmail -t
