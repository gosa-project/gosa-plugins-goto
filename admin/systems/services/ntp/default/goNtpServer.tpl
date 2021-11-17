<div class="ntp-wrapper">
    <div class="row">
        <div class="col s12 xl12">
            <h3>{t}Time server{/t}</h3>

            {render acl=$goTimeSourceACL}
            <div class="input-field">
                <select style="width:100%;" id="goTimeEntry" name="goTimeSource[]" size=8 multiple>
                 {html_options values=$goTimeSource output=$goTimeSource}
                </select>
            </div>
            {/render}

            {render acl=$goTimeSourceACL}
            <div class="input-field add">
                <input type="text" name="NewNTPExport"  id="NewNTPExportId">
                <button class="btn-small" type='submit' name='NewNTPAdd' id="NewNTPAddId">{msgPool type=addButton}</button>
                <button class="btn-small" type='submit' name='DelNTPEnt' id="DelNTPEntId">{msgPool type=delButton}</button>
            </div>
            {/render}
        </div>
    </div>
</div>

<div class="card-action">
 <button class="btn-small primary" type='submit' name='SaveService'>{msgPool type=saveButton}</button>
 <button class="btn-small primary" type='submit' name='CancelService'>{msgPool type=cancelButton}</button> 
</div>
