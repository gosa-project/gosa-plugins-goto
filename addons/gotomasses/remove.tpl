<div style="font-size:18px;">
 <img alt="" src="images/button_cancel.png" align=top>&nbsp;{t}Warning{/t}
</div>
<p>
  {$info}
</p>

<p>
 {t}So - if you're sure - press 'Delete' to continue or 'Cancel' to abort.{/t}
</p>

<p class="plugbottom">
{if $multiple}
  <input type=submit name="delete_multiple_confirm" value="{t}Delete{/t}">
{else}
  <input type=submit name="delete_confirm" value="{t}Delete{/t}">
{/if}
  <input type=submit name="delete_cancel" value="{t}Cancel{/t}">
</p>
