<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<style type="text/css">

.ObjectListViewport {
	width:100%;
	height:100%;
	border-collapse:collapse;
}

.ObjectListViewport_Header_Table {
	width:100%;
	border: 0px;
	border-collapse:collapse;
}	
	
.ObjectListViewport_Entry_Table {
	width:100%;
	border: 0px;
	border-collapse:collapse;
}

.ObjectListViewport_Entry_Cover{

	border: 0px;
	margin:0px;
	padding:0px;
}

.ObjectListViewport_Footer_Table {
    width:100%;
    border: 0px;
    border-collapse:collapse;
}


.ObjectListViewport_Table {
	border-collapse:collapse;
    width:100%;
	height:100%;
	border: 0px;
}

.ObjectListViewport_TD_Header {
	height:20px;
	background-color: #CCCCCC;
	vertical-align:middle;
	border: 0px;
	margin:0px;
	padding:0px;
}
.ObjectListViewport_TD_Entries {
	vertical-align:middle;
	border: 0px;
	margin:0px;
	padding:0px;
}
.ObjectListViewport_TD_Footer {
	height:20px;
	background-color: #CCCCCC;
	vertical-align:middle;
	border: 0px;
	margin:0px;
	padding:0px;
}
.ObjectListViewport_Entry_Cell {
	border-left: solid 1px;
	font-size:10px;
	height:18px;
}

</style>
<script type="text/javascript">

/* Register resize event to force redraw of all 
 *  displayed lists 
 */
window.onload = updateObjectListViewportSize;
window.onresize = updateObjectListViewportSize;

	function updateObjectListViewportSize() {

		var dbg = document.getElementById('debug');

		/* Somehow IE do not need to be resized 
         *  So skip the following part if the client uses ie
         */
		if(document.all){
			document.getElementById('ObjectListViewport_Entry_Cover').style.height= "100%";
			return;
		}
	
		/* Set Viewport to min height, to ensure 
         *  that resize will work correctly in konqueror 
         */
		document.getElementById('ObjectListViewport_Entry_Cover').style.height= "50px";

		/* Get values of displayed header and footer heights to be 
		 *  able to recalculate the Viewport 
         */
		var viewport	= getObjectHeight('ObjectListViewport_Table');
		var header  	= getObjectHeight('ObjectListViewport_TD_Header');
		var footer  	= getObjectHeight('ObjectListViewport_TD_Footer');

		/* Calculate the new visible entry part height. */
		var calc = (viewport  - ( header + footer ));
		document.getElementById('ObjectListViewport_Entry_Cover').style.height = calc;

		/* Reduce width of entry list, we need some space to 
         *  display the scrollbar without breaking the layout
         */
		var viewport = getObjectWidth('ObjectListViewport_Table');
		document.getElementById('ObjectListViewport_Entry_Table').style.width = (viewport - 16) + 'px';
	}


	/* Return integer value of style attribute width for specified ID  */
	function getObjectWidth(obj){
		obj = getComputedStyle(document.getElementById(obj),"").width;
		return(parseInt(obj.replace(/px/,'')));	
	}

	/* Return integer value of style attribute height for specified ID  */
	function getObjectHeight(obj){
		obj = getComputedStyle(document.getElementById(obj),"").height;
		return(parseInt(obj.replace(/px/,'')));
	}	
</script>
</head>
<body>
<input type='text' id='debug' value="" style='width:100%;'>
	<table style='height:90%;width:90%;background-color:#DDDDDD; border: solid 1px;'
		cellspacing=0 cellpadding=0>
		<tr>
			<td style='width:30%;height:50%;background-color:#EEEEEE;'>
				hallo<br>
				hallo<br>
				hallo<br>
				hallo<br>
				hallo<br>
				hallo<br>
			</td>
			<td style='background-color:#EEEEEE;'>
				<?php
				echo passthru("./test");
				?>
			</td>
		</tr>
		<tr>
			<td style='background-color:#999777;'>
				hallo<br>
				hallo<br>
			</td>
			<td style='background-color:#AAA006;'>
				hallo<br>
				hallo<br>
			</td>
		</tr>
	</table>
<script type="text/javascript">
	document.getElementById('ObjectListViewport_Entry_Cover').style.height= "50px";
</script>
</body>
</html>
