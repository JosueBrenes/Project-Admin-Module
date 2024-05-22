<?php

//? VISTA

/**
 * Implements hook_views_default_views().
 */

 function project_manager_views_default_views() {

  $view = new view();
  $view->name = 'tasks';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Tasks';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Tasks';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    1 => '1',
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Restablecer';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« primero';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ anterior';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'siguiente ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'último »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'body' => 'body',
    'field_consolas' => 'field_consolas',
    'field_existencias' => 'field_existencias',
    'field_precio' => 'field_precio',
    'delete_node' => 'delete_node',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['class'] = '';
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_consolas' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_existencias' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_precio' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Encabezado: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Add Task';
  $handler->display->display_options['header']['area']['content'] = '<?php

  // Generar URL para agregar una tarea
  $task_add_url = url(\'tasks/add\');

  // Generar URL para exportar el reporte
  $task_export_url = url(\'tasks/export\');

  echo \'<a href="\' . $task_add_url . \'" class="btn agregar-contenido" style="margin: 1rem 0;">Add Task</a>\';
  echo \'<a href="\' . $task_export_url . \'" class="btn agregar-contenido" style="margin: 1rem 0;">Generate Report</a>\';

  ?>

  ';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  /* Campo: Contenido: Task Name */
  $handler->display->display_options['fields']['field_task_name']['id'] = 'field_task_name';
  $handler->display->display_options['fields']['field_task_name']['table'] = 'field_data_field_task_name';
  $handler->display->display_options['fields']['field_task_name']['field'] = 'field_task_name';
  /* Campo: Contenido: Descripción */
  $handler->display->display_options['fields']['field_task_description']['id'] = 'field_task_description';
  $handler->display->display_options['fields']['field_task_description']['table'] = 'field_data_field_task_description';
  $handler->display->display_options['fields']['field_task_description']['field'] = 'field_task_description';
  /* Campo: Contenido: Start Date */
  $handler->display->display_options['fields']['field_task_start_date']['id'] = 'field_task_start_date';
  $handler->display->display_options['fields']['field_task_start_date']['table'] = 'field_data_field_task_start_date';
  $handler->display->display_options['fields']['field_task_start_date']['field'] = 'field_task_start_date';
  $handler->display->display_options['fields']['field_task_start_date']['settings'] = array(
    'format_type' => 'long',
    'custom_date_format' => '',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
    'show_repeat_rule' => 'show',
  );
  /* Campo: Contenido: End Date */
  $handler->display->display_options['fields']['field_task_end_date']['id'] = 'field_task_end_date';
  $handler->display->display_options['fields']['field_task_end_date']['table'] = 'field_data_field_task_end_date';
  $handler->display->display_options['fields']['field_task_end_date']['field'] = 'field_task_end_date';
  $handler->display->display_options['fields']['field_task_end_date']['settings'] = array(
    'format_type' => 'long',
    'custom_date_format' => '',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
    'show_repeat_rule' => 'show',
  );
  /* Campo: Contenido: Estado */
  $handler->display->display_options['fields']['field_task_status']['id'] = 'field_task_status';
  $handler->display->display_options['fields']['field_task_status']['table'] = 'field_data_field_task_status';
  $handler->display->display_options['fields']['field_task_status']['field'] = 'field_task_status';
  /* Campo: Contenido: Priority */
  $handler->display->display_options['fields']['field_task_priority']['id'] = 'field_task_priority';
  $handler->display->display_options['fields']['field_task_priority']['table'] = 'field_data_field_task_priority';
  $handler->display->display_options['fields']['field_task_priority']['field'] = 'field_task_priority';
  /* Campo: Contenido: Project Reference */
  $handler->display->display_options['fields']['field_project_reference']['id'] = 'field_project_reference';
  $handler->display->display_options['fields']['field_project_reference']['table'] = 'field_data_field_project_reference';
  $handler->display->display_options['fields']['field_project_reference']['field'] = 'field_project_reference';
  $handler->display->display_options['fields']['field_project_reference']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Sort criterion: Contenido: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Contenido: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['required'] = TRUE;
  /* Filter criterion: Contenido: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'task' => 'task',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'Agregar Videojuegos';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenido: Task Name */
  $handler->display->display_options['fields']['field_task_name']['id'] = 'field_task_name';
  $handler->display->display_options['fields']['field_task_name']['table'] = 'field_data_field_task_name';
  $handler->display->display_options['fields']['field_task_name']['field'] = 'field_task_name';
  /* Campo: Contenido: Descripción */
  $handler->display->display_options['fields']['field_task_description']['id'] = 'field_task_description';
  $handler->display->display_options['fields']['field_task_description']['table'] = 'field_data_field_task_description';
  $handler->display->display_options['fields']['field_task_description']['field'] = 'field_task_description';
  /* Campo: Contenido: Start Date */
  $handler->display->display_options['fields']['field_task_start_date']['id'] = 'field_task_start_date';
  $handler->display->display_options['fields']['field_task_start_date']['table'] = 'field_data_field_task_start_date';
  $handler->display->display_options['fields']['field_task_start_date']['field'] = 'field_task_start_date';
  $handler->display->display_options['fields']['field_task_start_date']['settings'] = array(
    'format_type' => 'long',
    'custom_date_format' => '',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
    'show_repeat_rule' => 'show',
  );
  /* Campo: Contenido: End Date */
  $handler->display->display_options['fields']['field_task_end_date']['id'] = 'field_task_end_date';
  $handler->display->display_options['fields']['field_task_end_date']['table'] = 'field_data_field_task_end_date';
  $handler->display->display_options['fields']['field_task_end_date']['field'] = 'field_task_end_date';
  $handler->display->display_options['fields']['field_task_end_date']['settings'] = array(
    'format_type' => 'long',
    'custom_date_format' => '',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
    'show_repeat_rule' => 'show',
  );
  /* Campo: Contenido: Estado */
  $handler->display->display_options['fields']['field_task_status']['id'] = 'field_task_status';
  $handler->display->display_options['fields']['field_task_status']['table'] = 'field_data_field_task_status';
  $handler->display->display_options['fields']['field_task_status']['field'] = 'field_task_status';
  /* Campo: Contenido: Priority */
  $handler->display->display_options['fields']['field_task_priority']['id'] = 'field_task_priority';
  $handler->display->display_options['fields']['field_task_priority']['table'] = 'field_data_field_task_priority';
  $handler->display->display_options['fields']['field_task_priority']['field'] = 'field_task_priority';
  /* Campo: Contenido: Project Reference */
  $handler->display->display_options['fields']['field_project_reference']['id'] = 'field_project_reference';
  $handler->display->display_options['fields']['field_project_reference']['table'] = 'field_data_field_project_reference';
  $handler->display->display_options['fields']['field_project_reference']['field'] = 'field_project_reference';
  $handler->display->display_options['fields']['field_project_reference']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Campo: Contenido: Link to edit content */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Campo: Contenido: Link to delete content */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['path'] = 'tasks/list';
  $handler->display->display_options['menu']['title'] = 'Agregar';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Adjunto */
  $handler = $view->new_display('attachment', 'Adjunto', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['path'] = 'tasks/export';
  $translatables['tasks'] = array(
    t('Master'),
    t('Tasks'),
    t('more'),
    t('Apply'),
    t('Restablecer'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« primero'),
    t('‹ anterior'),
    t('siguiente ›'),
    t('último »'),
    t('Add Task'),
    t('<?php

  // Generar URL para agregar una tarea
  $task_add_url = url(\'tasks/add\');

  // Generar URL para exportar el reporte
  $task_export_url = url(\'tasks/export\');

  echo \'<a href="\' . $task_add_url . \'" class="btn agregar-contenido" style="margin: 1rem 0;">Add Task</a>\';
  echo \'<a href="\' . $task_export_url . \'" class="btn agregar-contenido" style="margin: 1rem 0;">Generate Report</a>\';

  ?>

  '),
    t('Task Name'),
    t('Descripción'),
    t('Start Date'),
    t('End Date'),
    t('Estado'),
    t('Priority'),
    t('Project Reference'),
    t('Published status'),
    t('Page'),
    t('Agregar Videojuegos'),
    t('Link to edit content'),
    t('Link to delete content'),
    t('Adjunto'),
    t('Data export'),
  );
  }