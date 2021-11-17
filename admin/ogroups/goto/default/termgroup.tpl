<div class="termgroup-wrapper">
  <p>
    <b>{t}Warning{/t}:</b>&nbsp;{t}Actions you choose here influence all systems in this object group. Additionally, all
    values editable here can be inherited by the clients assigned to this object group.{/t}
  </p>

  <div class="row">
    <h3>{t}Generic{/t}</h3>
    <div class="col s12 xl6">
      <h4>{t}System settings{/t}</h4>
      {render acl=$gotoNtpServerACL}
      <div class="input-field">
        <select name="gotoNtpServerSelected[]" id="gotoNtpServerSelected" multiple size=5 style="width:100%;"
          title="{t}Choose server to use for synchronizing time{/t}" {if $inheritTimeServer} disabled {/if}>
          {html_options options=$gotoNtpServer_select}
        </select>
        <label for="gotoNtpServerSelected">{t}NTP server{/t}</label>
      </div>
      {/render}

      {render acl=$gotoNtpServerACL}
      <div class="input-field add">
        <select name="gotoNtpServers" id="gotoNtpServers" {if $inheritTimeServer} disabled {/if} size=1>
          {html_options output=$gotoNtpServers values=$gotoNtpServers}
        </select>
        <button class="btn-small" type='submit' name='addNtpServer' id="addNtpServer" {if ($inheritTimeServer) ||
          (!$gotoNtpServers)}disabled{/if}>{msgPool type=addButton}</button>
        <button class="btn-small" type='submit' name='delNtpServer' id="delNtpServer" {if ($inheritTimeServer) ||
          (!$gotoNtpServer_select)}disabled{/if}>{msgPool type=delButton}</button>
      </div>
      {/render}
    </div>

    <div class="col s12 xl6">
      <h4>{t}Goto settings{/t}</h4>

      {render acl=$gotoModeACL}
      <div class="input-field">
        <select name="gotoMode" title="{t}Select terminal mode{/t}" size=1>
          {html_options options=$modes selected=$gotoMode_select}
        </select>
        <span>{t}Mode{/t}</span>
      </div>
      {/render}

      {render acl=$gotoSyslogServerACL}
      <div class="input-field">
        <select id="gotoSyslogServer" name="gotoSyslogServer" title="{t}Choose server to use for logging{/t}" size=1>
          {html_options values=$syslogservers output=$syslogservers selected=$gotoSyslogServer_select}
        </select>
        <label for="gotoSyslogServer">{t}Syslog server{/t}</label>
      </div>
      {/render}

      {if $is_termgroup}
      {render acl=$gotoTerminalPathACL}
      <div class="input-field">
        <select name="gotoTerminalPath" id="gotoTerminalPath" title="{t}Select NFS root file system to use{/t}" size=1>
          {html_options options=$nfsservers selected=$gotoTerminalPath_select}
        </select>
        <label for="gotoTerminalPath">{t}Root server{/t}</label></td>
      </div>
      {/render}

      {render acl=$gotoSwapServerACL}
      <div class="input-field">
        <select name="gotoSwapServer" id="gotoSwapServer" title="{t}Choose NFS file system to place swap files on{/t}"
          size=1>
          {html_options options=$swapservers selected=$gotoSwapServer_select}
        </select>
        <label for="gotoSwapServer">{t}Swap server{/t}</label>
      </div>
      {/render}
      {/if}
    </div>
  </div>

  <hr class="divider">

  <div class="row">
    <div class="col s12 xl12">
      <label>
        <input type='checkbox' value='1' {if $members_inherit_from_group} checked
          {/if}name='members_inherit_from_group'>
        <span>{t}Inherit all values to group members{/t}</span>
      </label>
      <input name="workgeneric_posted" value="1" type="hidden">

      <h4>{t}Action{/t}</h4>

      {render acl=$FAIstateACL}
      <div class="input-field add">
        <select size="1" name="saction" title="{t}Select action to execute for this terminal{/t}">
          <option>&nbsp;</option>
          {html_options options=$actions}
        </select>
        <button class="btn-small" type='submit' name='action'>{t}Execute{/t}</button>
      </div>
      {/render}
    </div>
  </div>
</div>