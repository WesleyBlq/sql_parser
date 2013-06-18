
<BODY style="MARGIN: 10px"><DIV>
<DIV>﻿说明</DIV>
<DIV>=========</DIV>
<DIV>该项目为mysql&nbsp;sql解析器，词法分析和语法分析基于oceanbase&nbsp;0.4版本，后续的语法树解析和</DIV>
<DIV>sql语句优化分拆再次拼装代码正在编写，会陆续上传。</DIV>
<DIV>&nbsp;</DIV>
<DIV>编译：</DIV>
<DIV>STEP1：$&nbsp;sh&nbsp;gen_parser.sh</DIV>
<DIV>STEP2:&nbsp;$&nbsp;make</DIV>
<DIV>&nbsp;</DIV>
<DIV>执行：&nbsp;$&nbsp;./sql_parser</DIV>
<DIV>&nbsp;</DIV>
<DIV>&nbsp;</DIV>
<DIV>例：</DIV>
<DIV>insert语句如下：</DIV>
<DIV>INSERT&nbsp;INTO&nbsp;Persons&nbsp;(LastName,&nbsp;Address)&nbsp;VALUES&nbsp;('Wilson',&nbsp;'Champs-Elysees')\n</DIV>
<DIV>&nbsp;</DIV>
<DIV>解析后的语法树：</DIV>
<DIV>|-T_STMT_LIST</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;|-T_INSERT</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_IDENT&nbsp;:&nbsp;persons</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_COLUMN_LIST</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_IDENT&nbsp;:&nbsp;lastname</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_IDENT&nbsp;:&nbsp;address</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_VALUE_LIST</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_VALUE_VECTOR</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_STRING&nbsp;:&nbsp;Wilson</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_STRING&nbsp;:&nbsp;Champs-Elysees</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-NULL</DIV>
<DIV>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|-T_BOOL&nbsp;:&nbsp;FALSE</DIV>
<DIV>&nbsp;</DIV>
<DIV>&nbsp;</DIV>
<DIV>&nbsp;</DIV>
<DIV></DIV>
<DIV>DATE&nbsp;:&nbsp;2013.6.17&nbsp;</DIV>
<DIV>EMAIL:&nbsp;gqinbo@gmail.com</DIV></DIV></BODY>


