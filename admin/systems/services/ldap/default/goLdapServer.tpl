<div class="ldapServer-wrapper">
    <h3>{t}LDAP service{/t}</h3>
    
    {render acl=$goLdapBaseACL}
    <div class="input-field">
        <input type="text" size="80" value="{$goLdapBase}"  name="goLdapBase" id="goLdapBaseId">
        <label for="goLdapBaseId">{t}LDAP URI{/t}{$must}</label> 
    </div>
    {/render}

</div>

<div class="card-action">
    <button class="btn-small primary" type='submit' name='SaveService'>{msgPool type=saveButton}</button>
    <button class="btn-small primary" type='submit' name='CancelService'>{msgPool type=cancelButton}</button>
</div>
<input type="hidden" name="goLdapServerPosted" value="1">
