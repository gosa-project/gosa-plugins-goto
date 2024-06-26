<?php
/*
 * This code is part of GOsa (http://www.gosa-project.org)
 * Copyright (C) 2003-2008 GONICUS GmbH
 *
 * ID: $$Id$$
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

class EventAddSystemDialog extends management
{
  // Tab definition 
  protected $skipFooter = TRUE;
  protected $skipHeader = TRUE;

  function __construct($config,$ui)
  {
    $this->config = $config;
    $this->ui = $ui;
    $this->storagePoints = array(
        get_ou("servgeneric", "serverRDN"), 
        get_ou("workgeneric", "workstationRDN"), 
        get_ou("group", "ogroupRDN"), 
        get_ou("termgeneric", "terminalRDN"));

    // Build filter
    if (session::global_is_set(get_class($this)."_filter")){
      $filter= session::global_get(get_class($this)."_filter");
    } else {
      $filter = new filter(get_template_path("../../addons/goto/events/eventTargetSystems-filter.xml", TRUE));
      $filter->setObjectStorage($this->storagePoints);
    }
    $this->setFilter($filter);

    // Build headpage
    $headpage = new listing(get_template_path("../../addons/goto/events/eventTargetSystems-list.xml", TRUE));
    $headpage->setFilter($filter);
    parent::__construct($config, $ui, "object", $headpage);
  }

  function save_object() {}

  function save()
  {
    $act = $this->detectPostActions();
    $headpage = $this->getHeadpage();
    if(!isset($act['targets'])) return(array());
    $ret = array();
    foreach($act['targets'] as $dn){
      $ret[] = $headpage->getEntry($dn);
    }
    return($ret);
  }

  function get_selected_targets()
  {
    // Collect mac addresses 
    $entries = $this->save();
    $macs = array();
    $ldap = $this->config->get_ldap_link();
    $ldap->cd($this->config->current['BASE']);
    $member_dns = array();
    foreach($entries as $entry){
      $member_dns[] = $entry['dn'];
      if(in_array_strict("gosaGroupOfNames", $entry['objectClass'])){
        $ldap->cat($entry['dn']);
        if($ldap->count()){
          $attrs = $ldap->fetch();
          if(isset($attrs['member'])){
            for($i =0 ; $i< $attrs['member']['count']; $i++){
              $member_dns[] = $attrs['member'][$i];
            }
          }
        }
      }
    }
    foreach($member_dns as $dn){
      $ldap->cat($dn, array('macAddress')); 
      if($ldap->count()){
        $attrs = $ldap->fetch();
        if(isset($attrs['macAddress'])){
          $macs[] = $attrs['macAddress'][0];
        }
      }
    }
    return($macs);
  }
}

?>
