<div class="terminal-wrapper">
  <div class="row">
    <div class="col s12 xl12">
      <h3>{t}Terminal service{/t}</h3>
      {render acl=$goXdmcpIsEnabledACL}
      <label>
        <input type="checkbox" value="true" name="goXdmcpIsEnabled" id="Temporariid" {if $goXdmcpIsEnabled} checked
          {/if}>
        <span>{t}Temporary disable login{/t}</span>
      </label>
      {/render}

      <h3>{t}Supported session types{/t}</h3>

      {foreach from=$gotoSessionTypes item=item key=key}
      <label>
        <input class="center" type="checkbox" name="gotoSessionType_{$key}" {if $item} checked {/if}>
        <span>{$key}</span>
      </label>
      {/foreach}
    </div>
  </div>
</div>

<div class="card-action">
  <button class="btn-small primary" type='submit' name='SaveService'>{msgPool type=saveButton}</button>
  <button class="btn-small primary" type='submit' name='CancelService'>{msgPool type=cancelButton}</button>
</div>
<input type="hidden" name="goTerminalServerPosted" value="1">