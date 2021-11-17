<div class="logonManagement-wrapper">
	<div class="row">
		<h3>{t}Log on script management{/t}</h3>
		<div class="col s12 xl6">
			<h4>{t}Log on script settings{/t}</h4>

			<input type="hidden" name="dialogissubmitted" value="1">

			<div class="input-field">
				<input type="text" size=20 value="{$LogonName}" name="LogonName" {$LogonNameACL} id="LogonName">
				<label for="LogonName">{t}Script name{/t}</label>
			</div>

			<div class="input-field">
				<input type="text" size=40 value="{$LogonDescription}" name="LogonDescription" id="LogonDescription">
				<label for="LogonDescription">{t}Description{/t}</label>
			</div>

			<div class="input-field">
				<select name="LogonPriority" id="LogonPriority" size=1>
					{html_options values=$LogonPriorityKeys output=$LogonPrioritys selected=$LogonPriority}
				</select>
				<label>{t}Priority{/t}</label>
			</div>
		</div>

		<div class="col s12 xl6">
			<h4>{t}Log on script flags{/t}</h4>

			<label>
				<input type="checkbox" value="L" name="LogonLast" {$LogonLastCHK} id="LogonLast">
				<span>{t}Last script{/t}</span>
			</label>

			<label>
				<input type="checkbox" value="O" name="LogonOverload" {$LogonOverloadCHK} id="LogonOverload">
				<span>{t}Script can be replaced by user{/t}</span>
			</label>
		</div>
	</div>

	<hr class="divider">

	<div class="row">
		<h3>{t}Script{/t}</h3>
		<div class="col s12 xl6">
			<h4>{t}Log on script{/t}</h4>

			<div class="input-field">
				<textarea name="LogonData">{$LogonData}</textarea>
			</div>

			<div class="input-field add">
				<input type="file" name="importFile" id="importFile">
				<button class="btn-small" type='submit' name='StartImport'>{t}Import{/t}</button>
			</div>
		</div>
	</div>
</div>

<div class="card-action">
	<button class="btn-small primary" type='submit' name='LogonSave'>{msgPool type=applyButton}</button>
	<button class="btn-small primary" type='submit' name='LogonCancel'>{msgPool type=cancelButton}</button>
</div>

<script language="JavaScript" type="text/javascript">
	// First input field on page
	focus_field('LogonName');
</script>