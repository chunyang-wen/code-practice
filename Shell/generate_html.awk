#/bin/env awk -f

BEGIN{
    FS="\t";
    OFS="\t";
    print "<html>"
    print "<title>–≈œ¢¡˜titleµÕÀ◊∆¿º€</title>";
    print "<meta name=""viewport"" content=""width=device-width,target-densitydpi=device-dpi,user-scalable=no>""</meta>"
    print "<body>"
}

{

    printf("%s\n","=================="FNR"=====================")
    k[FNR] = $1;
    t[FNR] = $2;
    c[FNR] = $3;
    m[FNR] = $4;
    print "<p style=""font-weight:bold"">Õ∆¥ :  "$1"</p>";
    print "<p style=""font-weight:bold"">Title:  "$2"</p>";
    print "<p style=""font-weight:bold"">""µ„ª˜¥Æ""</p>";
    print "<a target=""_blank"" href="$3">"$3"</a>";
    #print "<p style=""font-weight:bold>≈‰Õº-280*200""</p>";
    #print "<img src="$4">""</img>";
    print "<p style=""font-weight:bold>≈‰Õº-600*300""</p>";
    print "<img src="$4" style=""width:600px;height:300px"">""</img>";
    print "<p style=""font-weight:bold>≈‰Õº-640*270""</p>";
    print "<img src="$4" style=""width:600px;height:300px"">""</img>";

    print "<br/>"
    printf("%s\n","=================="FNR"=====================")
    print "<br/>"

    }
    END {
        print "</body></html>";
        }
