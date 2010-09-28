<?php

/*! \brief  The base class for all template-widgets used by the 
 *           device-configuration class.
 */
class TemplateWidget
{
    protected $name = "unnamed";
    protected $value = "";

    protected $description = "";
    protected $required = "";
    protected $type = "";
    protected $display = "";

    /*! \brief  Constructs the template widget and sets the default values.
     *  @param  Config  The GOsa configuration object.
     *  @param  String  A name for the widget.
     *  @param  String  The initial value.
     *  @param  String  A description.
     *  @param  String  True/False  Must-Value/Optional-Value.
     *  @param  String  The widget type. 
     *  @param  String  A display name for the widget.
     */
    function __construct(&$config, $name, $value, $description,$required,$type,$display)
    {
        $this->config = &$config;
        $this->name = $name;
        $this->value = $value;
        $this->description = $description;
        $this->required = $required;
        $this->type = $type;
        $this->display = $display;
        $class = get_class();
        $this->postName = "{$class}_{$this->name}";
    }


    /*! \brief  Returns the display-name for the current widget.
     *  @return  String     The display-name for the widget, this 
     *                       name will usually be rendered infront of input fields.
     */
    function getDisplayName()
    {
        return($this->display);
    }


    /*! \brief  Generates the HTML code for the widget.
     *  @return  The HTML content for the widget.
     */
    function render()
    {
        return("");
    }


    /*! \brief  Keep track of posted values.
     */
    function save_object()
    {
        if(isset($_POST[$this->postName])){
            $this->value = get_post($this->postName);
        }
    }


    /*! \brief  Returns the current value.
     *  @return  Mixed  The widgets value.
     */
    function getValue()
    {
        return($this->value);
    }


    /*! \brief  Returns the name of the widget.
     *  @param  String  The widgets name.
     */
    function getName()
    {
        return($this->name);
    }


    /*! \brief  Sets a new value for the widget.
     *  @param  String  The new value.
     */
    function setValue($value)
    {
        $this->value = $value;
    }
}
?>