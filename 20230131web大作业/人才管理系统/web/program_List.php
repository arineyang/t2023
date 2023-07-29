<?php  
include("conn.php");error_reporting(E_ALL ^ E_NOTICE);

?>
<!DOCTYPE html>
<html>
<head>
<html>
  <head>
   <title>项目信息管理页面</title>
              <link href="css/gzf.css" rel="stylesheet" type="text/css" />
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  </head>
<body >

 <div class="bodydiv">
<table width="1000" align="center" border="1" cellspacing="0" cellpadding="5">
<tr class="myTRHead">
 <td class="myTDHead"  >
项目信息管理 </td>
 </tr>
            <tr class="myTRHead">
            <td   align="left">
<form name="form1" id="form1" method="post" action="program_List.php">
项目名称：<input name=title type="text" id=title />
项目类型：<input name=type type="text" id=type />
      <input type="submit" name="Submit" value="查询" />
</form>
 <tr>
    <td align="left">
           <table cellspacing="0" cellpadding="4" border="0"  style="color:#333333;width:830px;border-collapse:collapse;text-align: left">
		<tr>
			<th align="left" scope="col">项目编号</th>
       <th align="left" scope="col">项目名称</th>
       <th align="left" scope="col">项目类型</th>
       <th align="left" scope="col">项目内容</th>
        <th scope="col">操作</th>

		</tr>
 <?php
 
 $sql="select * from program where 1=1";//定义SQL语句
if ($_POST["title"]!=""){$sql=$sql." and title like '%$_POST[title]%'";}//当有查询条件时的操作
if ($_POST["type"]!=""){$sql=$sql." and type like '%$_POST[type]%'";}//当有查询条件时的操作


  $state = $pdo->query($sql); 
			//获取结果集中的所有数据
	        $res = $state->fetchAll(PDO::FETCH_ASSOC);
			
  foreach ($res as $key => $value) 
{
?>
		<tr>
<td> <?php echo $value['id']; ?>  </td>
 
 
 <td><?php echo $value['title']?></td>
<td><?php echo $value['type']?></td>
<td><?php echo $value['content']?></td>
 <td><a href=programedit.php?action=mod&id=<?php echo $value['id']?>&tn=program">修改</a>  
  <a href="delprogram.php?id=<?php echo $value['id']?>&tn=program" onClick="return confirm('真的要删除？')">删除</a></td>
		  </tr>
		   <?php 
		    }
		      ?>
		      </table>
     </div>
</body>
</html>

