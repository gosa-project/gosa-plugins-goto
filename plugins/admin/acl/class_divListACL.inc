<?php

class divListACL extends MultiSelectWindow
{

  /* Current base */
  var $selectedBase       = "";
  var $departments        = array();

  /* Regex */
  var $Regex              = "*";

  /* CheckBoxes */

  /* Subsearch checkbox */
  var $SubSearch              = false;

  var $parent             ;
  var $ui                 ;
  var $action_col_size;
  

  function divListACL ($config,$parent)
  {
    MultiSelectWindow::MultiSelectWindow($config, "ACLs", "acl");
    
    $this->parent       = $parent;
    $this->ui           = get_userinfo();

    /* Set list strings */
    $this->SetTitle(_("List of acl"));
    $this->SetSummary(_("List of acls"));

    /* Result page will look like a headpage */
    $this->SetHeadpageMode();
    $this->SetInformation(_("This menu allows you to edit and delete selected acls."));

    $this->EnableAplhabet   (true);
  
    /* Disable buttonsm */
    $this->EnableCloseButton(false);
    $this->EnableSaveButton (false);

    /* Dynamic action col */
    $this->action_col_size = 120;

    /* set Page header */
    $this->AddHeader(array("string"=>"&nbsp;",          "attach"=>"style='width:20px;'"));
    $this->AddHeader(array("string"=>_("Summary")));
    $this->AddHeader(array("string"=>_("Actions"),      "attach" => "style='width:".$this->action_col_size."px;border-right:0px;text-align:right;'"));

    /* Set dynamically filter checkboxes */
    $this->set_filter_objectclasses();   
 
    /* Add SubSearch checkbox */
    $this->AddCheckBox("SubSearch",  _("Select to search within subtrees"), _("Ignore subtrees"), false);


    /*                  Name                 ,Text                              ,Default  , Connect with alphabet  */
    $this->AddRegex   ("Regex",     _("Display acls matching"),"*" , true);
  }


  function GenHeader()
  {
     /* Prepare departments,
       which are shown in the listbox on top of the listbox
     */
    $options= "";
    $Copy_Paste = "";

    /* Get all departments within this subtree */
    $ui= get_userinfo();
    $first = "";
    $found = FALSE;
    $base = $this->config->current['BASE'];

    /* Add base */
    $tmp = array();
    $tmp[] = array("dn"=>$this->config->current['BASE']);
    $tmp=  array_merge($tmp,get_list("(&(|(ou=*)(description=*))(objectClass=gosaDepartment))", $this->module, $base,
                    array("ou", "description"), GL_SIZELIMIT | GL_SUBSEARCH));

    $deps = array();
    foreach($tmp as $tm){
      $deps[$tm['dn']] = $tm['dn'];
    }

    /* Load possible departments */
    $ui= get_userinfo();
    $tdeps= $ui->get_module_departments("acl");
    $ids = $this->config->idepartments;
    $first = "";
    $found = FALSE;
    foreach($ids as $dep => $name){
      if(isset($deps[$dep]) && in_array_ics($dep, $tdeps)){

        /* Keep first base dn in mind, we could need this
         *  info if no valid base was found
         */
        if(empty($first)) {
          $first = $dep['dn'];
        }

        $value = $ids[$dep];
        if ($this->selectedBase == $dep){
          $found = TRUE;
          $options.= "<option selected='selected' value='".$dep."'>$value</option>";
        } else {
          $options.= "<option value='".$dep."'>$value</option>";
        }
      }
    }

    /* The currently used base is not visible with your acl setup.
     * Set base to first useable base.
     */
    if(!$found){
      $this->selectedBase = $first;
    }

    /* Allow copy & paste for roles */ 
    $acl_all  = $ui->has_complete_category_acls($this->selectedBase,"acl");
    $acl      = $ui->get_permissions($this->selectedBase,"acl/acl");

    /* Add default header */
    $listhead = MultiSelectWindow::get_default_header();

    /* Get copy & paste icon */
    $Copy_Paste ="";
    if(preg_match("/(c.*w|w.*c)/",$acl_all) &&  $this->parent->CopyPasteHandler){
      $Copy_Paste = $this->parent->CopyPasteHandler->generatePasteIcon();
      $addsep = true;
    }

    /* Add snapshot icons */
    if(preg_match("/(c.*w|w.*c)/",$acl_all)){
      $listhead .= $this->get_snapshot_header($this->selectedBase);
      $add_sep = true;
    }

    if(preg_match("/c/",$ui->get_permissions($this->selectedBase,"acl/acl"))){
      $add_sep = true;
      $listhead .= "<input class='center' type='image' align='middle' src='images/list_new_acl_role.png'
        name='new_acl_role'     alt='"._("New acl role")."' title='"._("New acl role")."'>&nbsp;";
    }

    $listhead .= $Copy_Paste. 
      _("Base")."&nbsp;<select name='CurrentMainBase' onChange='mainform.submit()' class='center'>$options</select>".
      " <input class='center' type='image' src='images/list_submit.png' align='middle' 
      title='"._("Submit department")."' name='submit_department' alt='".  _("Submit")."'>&nbsp;".
      "</div>";

    $this->SetListHeader($listhead);
  }

  /* so some basic settings */
  function execute()
  {
    $this->ClearElementsList();
    $this->GenHeader();
  }

  function setEntries($list)
  {

    foreach($list as $key => $acl_entry){

      /* Get copy & paste icon */
      $acl        = $this->ui->get_permissions($acl_entry['dn'],"acl/acl");
      $acl_all    = $this->ui->has_complete_category_acls($acl_entry['dn'],"acl");
      $action     = "";

      if(in_array("gosaRole",$acl_entry['objectClass'])){

        /* Role handling */
        $editlink       = "<a href='?plug=".$_GET['plug']."&amp;id=%s&amp;act=list_edit_role'>%s</a>";
        $list_left_icon = "<img src='images/select_acl_role.png' alt='"._("Role")."'>";
        $cn = htmlentities(utf8_decode($acl_entry['cn'][0])) ;

        if(isset($acl_entry['description'][0])){
          $cn .= "&nbsp;[".$acl_entry['description'][0]."]";
        }

        /* Add copy & paste handler */
        if(($this->parent->CopyPasteHandler) && preg_match("/(c.*w|w.*c)/",$acl_all)){
          $action.= "<input class='center' type='image'
            src='images/editcut.png' alt='"._("cut")."' name='cut_%KEY%' title='"._("Cut this entry")."'>&nbsp;";
          $action.= "<input class='center' type='image'
            src='images/editcopy.png' alt='"._("copy")."' name='copy_%KEY%' title='"._("Copy this entry")."'>&nbsp;";
        }

        /* Add actions depending on acls */
        if(preg_match("/r/", $acl)){
          $action.= "<input class='center' type='image' src='images/edit.png' alt='"._("edit")."'     
            name='list_acl_role_edit_%KEY%' title='"._("Edit acl role")."'>";
        }

        /* Add snapshot functionality */
        if(preg_match("/(c.*w|w.*c)/", $acl_all)){
          $action.= $this->GetSnapShotActions($acl_entry['dn']);
        }

        if(preg_match("/d/", $acl)){
          $action.= "<input class='center' type='image' src='images/edittrash.png' alt='"._("delete")."' 
            name='list_acl_role_del_%KEY%' title='"._("Delete acl role")."'>";
        }
      }else{

        /* Acl handling */
        $editlink       = "<a href='?plug=".$_GET['plug']."&amp;id=%s&amp;act=list_edit_entry'>%s</a>";
        $list_left_icon = "<img src='images/select_acl.png' alt='"._("Acl")."'>";
        $cn = htmlentities(utf8_decode($acl_entry['dn'])); 

        /* Add actions depending on acls */
        if(preg_match("/r/", $acl)){
          $action.= "<input class='center' type='image' src='images/edit.png' alt='"._("edit")."'     
            name='list_acl_edit_%KEY%' title='"._("Edit acl")."'>";
        }
        if(preg_match("/d/", $acl)){
          $action.= "<input class='center' type='image' src='images/edittrash.png' alt='"._("delete")."' 
            name='list_acl_del_%KEY%' title='"._("Delete acl")."'>";
        }
      }

      $field1 = array("string" => $list_left_icon, "attach"=> "style='text-align:center;width:20px;'");
      $field2 = array("string" => sprintf($editlink,$key,$cn)."&nbsp;","attach" => "");
      $field3 = array("string" => preg_replace("/%KEY%/",$key,$action), "attach"=> "style='text-align:right;width:".$this->action_col_size."px;border-right:0px;'");
      $this->AddElement(array($field1,$field2,$field3));
    }
  }

  function Save()
  {
    MultiSelectWindow :: Save();  
  }

  function save_object()
  {
    /* Save automatic created POSTs like regex, checkboxes */
    MultiSelectWindow::save_object();   
  }


  /* Add some additional checkboxes to the filter part, this should be generated dynamically. */
  function set_filter_objectclasses()
  { 
  }
  
  /* Return objectClass names used in filter part */  
  function get_filter_objectclasses()
  {
    return(array("gosaAccount","gosaDepartment"));
  }

  
  /* Return plugin informations for acl handling */
  function plInfo()
  {
    return (array(
          "plShortName"   => _("ACL")."&nbsp;&amp;&nbsp;"._("ACL roles"),
          "plDescription" => _("ACL")."&nbsp;&amp;&nbsp;"._("ACL roles")."&nbsp;-&nbsp;("._("Access control list").")",
          "plSelfModify"  => FALSE,
          "plDepends"     => array(),
          "plPriority"    => 0,
          "plSection"     => array("administration"),
          "plCategory"    => array("acl" => array("description"  => _("ACL")."&nbsp;&amp;&nbsp;"._("ACL roles"),
                                                          "objectClass"  => array("gosaAcl","gosaRole"))),
          "plProvidedAcls"=> array(
            "cn"          => _("Role name"),
            "description" => _("Role description"))

          ));
  }



}
// vim:tabstop=2:expandtab:shiftwidth=2:filetype=php:syntax:ruler:
?>