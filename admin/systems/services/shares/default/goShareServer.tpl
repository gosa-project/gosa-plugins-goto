<div class="shares-wrapper">
  <div class="row">
    <div class="col s12 xl12">
      <h3>{t}Shares{/t}</h3>

      {render acl=$goExportEntryACL mode=read_active}
      <div class="input-field add">
        <select style="width:100%" id="goExportEntry" name="goExportEntryList[]" size=12 multiple>
          {html_options values=$goExportEntry output=$goExportEntryKeys}
        </select>
        {render acl=$goExportEntryACL}
        <button class="btn-small" type='submit' name='NewNfsAdd' id="NewNfsAddId" {if !$createable} disabled
          {/if}>{msgPool
          type=addButton}</button>
        {/render}
        {render acl=$goExportEntryACL mode=read_active}
        <button class="btn-small" type='submit' name='NewNfsEdit' id="NewNfsEditId">{t}Edit{/t}</button>
        {/render}
        {render acl=$goExportEntryACL}
        <button class="btn-small" type='submit' name='DelNfsEnt' id="DelNfsEntId" {if !$removeable} disabled
          {/if}>{msgPool type=delButton}</button>
        {/render}
      </div>
    </div>
  </div>
</div>

<div class="card-action">
  <button class="btn-small primary" type='submit' name='SaveService'>{msgPool type=saveButton}</button>
  <button class="btn-small primary" type='submit' name='CancelService'>{msgPool type=cancelButton}</button>
</div>
<input type="hidden" name="goShareServerPosted" value="1">