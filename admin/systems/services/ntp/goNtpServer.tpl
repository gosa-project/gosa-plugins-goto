<br>
<h2>{t}Time server{/t}</h2>
<br>
<table summary="" style="width:100%">
<tr>
 <td>
{render acl=$goNtpServerACL}
	<select style="width:100%;" id="goTimeEntry" name="goTimeSource[]" size=8 multiple>
		{html_options values=$goTimeSource output=$goTimeSource}
		<option disabled>&nbsp;</option>
	</select>
{/render}
<br>
{render acl=$goNtpServerACL}
	<input type="text" name="NewNTPExport"  id="NewNTPExportId">
{/render}
{render acl=$goNtpServerACL}
	<input type="submit"    value="{msgPool type=addButton}"      name="NewNTPAdd"  id="NewNTPAddId">
{/render}
{render acl=$goNtpServerACL}
	<input type="submit"    value="{msgPool type=delButton}"   name="DelNTPEnt"  id="DelNTPEntId">
{/render}
</td>
</tr>
</table>

<p class="seperator">&nbsp;</p>
<div style="width:100%; text-align:right;padding-top:10px;padding-bottom:3px;">
	<input type='submit' name='SaveService' value='{msgPool type=saveButton}'>
	&nbsp; 
	<input type='submit' name='CancelService' value='{msgPool type=cancelButton}'> 
</div>