<?php 
//包含数据库链接文件 
include("conn.php");
 date_default_timezone_set("PRC");//设置时区，默认为格林威治标准时间和北京时间大概差8个小时左
//获取页面的参数 
header("Content-Type:text/html;charset=utf-8");
if ($_POST) {
$id=$_GET['id'];
$cz=$_GET['action'];
 $title=$_POST['title']; 
 $type=$_POST['type']; 
 $content=$_POST['content'];
//判断参数看是添加还是修改的操作 
if( $cz=="xs")
 {
//定义更新的SQL语句 
$sql="update program set id='".$id."',title='".$title."',type='".$type."',content='".$content."' where id='". $id."'"; 
     
     $row = $pdo->exec($sql);
       // 判断是否成功！
       if ($row) {
      	echo "<script>alert('操作成功！');window.location.href='index.php'</script>";
       } else {
       	echo "<script>alert('操作失败！');window.location.href='program_List.php'</script>";
       }
     exit;
}}


if (!empty($_GET['id'])) {
	$cz=$_GET['action'];
	$id=$_GET['id'];
//如果是编辑操作，给字段赋值 
  if( $cz=="mod")
 {
  if( $id!="")
 {
  $sql="select * from program where id=".$id;
  
  $state = $pdo->query($sql);
  // 获取结果集中的数据,将其显示在表单中
  $info = $state->fetch(PDO::FETCH_ASSOC);
 
//获取数据库中的字段内容，并在页面显示 
 $id=$info['id'];
 $title=$info['title'];
 $type=$info['type'];
 $content=$info['content'];
 
 
 }
}
}

?><html>
  <head>

 <title>项目信息管理页面</title>
 
   	<meta charset="UTF-8">
   
   	<style>
   		input{
   			margin-left: 5px;
   		}
   	</style>
     
  </head>
<body >

    
 <div class="bodydiv">
  <form method="post" name="program"   action="programedit.php?action=xs&id=<?php echo $id?>">
 <table width="330" align="center" border="0" style="border: 2px solid #333;padding-top: 20px;" cellspacing="0" cellpadding="10">
 <tr class="myTRHead">
   <td class="myTDHead"  colspan="2" >项目信息管理页面</td>
  </tr>
  <tr>
   <td  align="right">项目名称:</td>
    <td align="left" >  <input name='title' type='text' id='title' value='<?php echo $title ?>' class="txtcss"  required />
 </td> 
  </tr>
  <tr>
   <td  align="right">项目类型:</td>
    <td align="left" >  <input name='type' type='text' id='type' value='<?php echo $type ?>' class="txtcss"  required />
 </td> 
  </tr>
  <tr>
   <td  align="right">项目内容:</td>
    <td align="left" >  <input name='content' type='text' id='content' value='<?php echo $content ?>' class="txtcss"  required />
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

