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

class DaemonEvent_installation_activation extends DaemonEvent
{
    public function __construct($config,$data = array())
    {
        DaemonEvent::__construct($config,$data);
        $this->s_Menu_Name  = _("Installation activation");
        $this->s_Event_Name = _("Installation activation");
        $this->s_Schedule_Action  = "job_set_activated_for_installation";
        $this->s_Trigger_Action   = "gosa_set_activated_for_installation";
        $this->s_Queued_Action    = "set_activated_for_installation";
        $this->s_Menu_Image = "images/true.png";
        $this->s_List_Image = "images/true.png";
    }

    public function execute()
    {
        DaemonEvent::execute();

        $display = $this->get_header();

        $tmp = $this->data;

        /* Check if target add dialog is open */
        if($this->is_target_list_open() && $this->is_new){
            return($this->get_target_add_list());
        }

        $smarty = get_smarty();
        $smarty->assign("data"        , $this->data);
        $smarty->assign("target_list" , $this->get_target_list());
        $smarty->assign("is_new"      , $this->is_new);
        $smarty->assign("timestamp"   , $this->get_time_select());
        $display.= $smarty->fetch(get_template_path('DaemonEvent_installation_activation.tpl', TRUE, dirname(__FILE__)));
        $display.= $this->get_footer();
        return($display);
    }

    public function save_object()
    {
        DaemonEvent::save_object();
    }
} 

?>
