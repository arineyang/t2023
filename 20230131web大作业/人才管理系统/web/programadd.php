<?php 
//包含数据库链接文件 
include("conn.php");
 date_default_timezone_set("PRC");//设置时区，默认为格林威治标准时间和北京时间大概差8个小时左
//获取页面的参数 
header("Content-Type:text/html;charset=utf-8");

if ($_POST) {
 
 $title=$_POST['title'];
 
 $type=$_POST['type'];
 
 $content=$_POST['content'];
//判断参数看是添加还是修改的操作 
 
$sql= "insert into program(title,type,content)values('".$title."','".$type."','".$content."')";
    echo $sql;
	 
      $row = $pdo->exec($sql);
      // 判断是否成功！
      if ($row) {
     	echo "<script>alert('添加成功！');window.location.href='index.php'</script>";
      } else {
      	echo "<script>alert('添加失败！');window.location.href='program_List.php'</script>";
      }
   	exit;
}
 
 
?><html>
  <head>

   <title>项目信息管理页面</title>
   
  	<meta charset="UTF-8">
  	<title>员工信息管理系统</title>
  	<style>
  		input{
  			margin-left: 5px;
  		}
  	</style>
  
  </head>
<body >
    

 <div class="bodydiv">
  <form method="post" name="program"   action="programadd.php">
  <table width="330" align="center" border="0" style="border: 2px solid #333;padding-top: 20px;" cellspacing="0" cellpadding="10">
 <tr class="myTRHead">
   <td class="myTDHead"  colspan="2" >项目信息管理页面</td>
  </tr>
  <tr>
   <td  align="right">项目名称:</td>
    <td align="left" >  <input name='title' type='text'    class="txtcss"  required />
 </td> 
  </tr>
  <tr>
   <td  align="right">项目类型:</td>
    <td align="left" >  <input name='type' type='text'   class="txtcss"  required />
 </td> 
  </tr>
  <tr>
   <td  align="right">项目内容:</td>
    <td align="left" >  <input name='content' type='text'  class="txtcss"  required />
 </td> 
  </tr>
<tr  >
    <td   align="right"></td>
    <td align="left">
                    <input type="submit" name="Submit" value="提交" onclick="return check();" class="btn"/>
 </td>
     </tr>

    </table>
</div>
     </form>
</body>
</html>

