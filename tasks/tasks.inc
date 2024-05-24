<?php

/**
 * Implementa un formulario para gestionar tareas.
 */
function task_manager_task_add_form($form, &$form_state) {
    global $user;
    
    // Verificar si el usuario es administrador.
    if (!user_access('administer tasks')) {
      return t('Access denied. You must have permission to view your own projects.');
  }
    
    // Campo de texto para el nombre de la tarea.
    $form['field_task_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Task Name'),
        '#required' => TRUE,
    );

  // Campo de texto largo para la descripción de la tarea.
    $form['field_task_description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#required' => TRUE,
    );
  
    // Campo de fecha para la fecha de inicio de la tarea.
    $form['field_task_start_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('Start Date'),
      '#date_format' => 'Y-m-d',
      '#required' => TRUE,
    );
  
    // Campo de fecha para la fecha de finalización de la tarea.
    $form['field_task_end_date'] = array(
      '#type' => 'date_popup',
      '#title' => t('End Date'),
      '#date_format' => 'Y-m-d',
      '#required' => TRUE,
    );
  
    // Campo de lista para el estado de la tarea.
    $form['field_task_status'] = array(
      '#type' => 'select',
      '#title' => t('Status'),
      '#options' => array(
        'in_progress' => t('In Progress'),
        'completed' => t('Completed'),
        'cancelled' => t('Cancelled'),
      ),
      '#required' => TRUE,
    );
  
    // Campo de lista para la prioridad de la tarea.
    $form['field_task_priority'] = array(
      '#type' => 'select',
      '#title' => t('Priority'),
      '#options' => array(
        1 => t('Low'), // Convertido a número
        2 => t('Medium'), // Convertido a número
        3 => t('High'), // Convertido a número
      ),
      '#required' => TRUE,
    );
  
    // Obtener nodos de tipo "project" para la referencia.
    $projects = array();
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'project');
    $result = $query->execute();
    
    if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);
      foreach ($nodes as $node) {
        $projects[$node->nid] = $node->title;
      }
    }
  
    // Campo de referencia a un proyecto.
    $form['field_project_reference'] = array(
      '#type' => 'select',
      '#title' => t('Project Reference'),
      '#options' => $projects,
      '#required' => TRUE,
    );
  
    // Botón de envío.
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Task'),
    );
  
    return $form;
  }

/**
 * Validar el formulario de tareas.
 */
function custom_task_form_validate($form, &$form_state) {
    // Verificar que ningún campo esté vacío.
    foreach ($form_state['values'] as $key => $value) {
        if (empty($value) && $key != 'field_project_reference' && $key != 'submit') {
            form_set_error($key, t('El campo @field es obligatorio.', array('@field' => $form[$key]['#title'])));
        }
    }

    // Obtener las fechas en formato "YYYY-MM-DD".
    $start_date = $form_state['values']['field_task_start_date'];
    $end_date = $form_state['values']['field_task_end_date'];
    
    // Verificar que las fechas sean válidas y la fecha de inicio sea anterior a la fecha de finalización.
    if (!empty($start_date) && !empty($end_date)) {
        $start_timestamp = strtotime($start_date);
        $end_timestamp = strtotime($end_date);
        
        if ($start_timestamp >= $end_timestamp) {
            form_set_error('field_task_end_date', t('La fecha de finalización debe ser posterior a la fecha de inicio.'));
        }
    }
}
  
/**
 * Enviar el formulario de tareas.
 */
function task_manager_task_add_form_submit($form, &$form_state) {
    global $user;

    // Crear un nuevo nodo de tipo "task".
    $node = new stdClass();
    $node->type = 'task'; // Tipo de nodo definido en tu instalación de Drupal.
    $node->uid = $user->uid;
    $node->status = 1; // Publicar el nodo automáticamente.
    node_object_prepare($node);

    // Asignar valores de los campos del formulario al nodo.
    $node->title = check_plain($form_state['values']['field_task_name']);
    $node->language = LANGUAGE_NONE;
    $node->field_task_name[LANGUAGE_NONE][0]['value'] = $form_state['values']['field_task_name'];
    $node->field_task_description[LANGUAGE_NONE][0]['value'] = $form_state['values']['field_task_description'];
    $node->field_task_start_date[LANGUAGE_NONE][0]['value'] = $form_state['values']['field_task_start_date'];
    $node->field_task_end_date[LANGUAGE_NONE][0]['value'] = $form_state['values']['field_task_end_date'];
    $node->field_task_status[LANGUAGE_NONE][0]['value'] = $form_state['values']['field_task_status'];

    // Asignar la prioridad según la selección del usuario.
    $priority = $form_state['values']['field_task_priority'];
    $priority_value = 1; // Valor predeterminado para la prioridad si la selección es inválida.
    switch ($priority) {
        case 'M':
            $priority_value = 2;
            break;
        case 'H':
            $priority_value = 3;
            break;
    }
    $node->field_task_priority[LANGUAGE_NONE][0]['value'] = $priority_value;
    
    // Obtener el ID del proyecto seleccionado.
    $project_id = $form_state['values']['field_project_reference'];
    // Asignar el proyecto como referencia.
    if (!empty($project_id)) {
        $node->field_project_reference[LANGUAGE_NONE][0]['target_id'] = $project_id;
    }

    // Guardar el nodo.
    $node_save_result = node_save($node);
    if ($node_save_result === FALSE) {
        // Hubo un problema al guardar el nodo. Obtener errores.
        $errors = drupal_get_messages('error');
        $error_message = '';
        if (!empty($errors['error'])) {
            $error_message = implode("\n", $errors['error']);
        }
        // Registrar un mensaje de error con información adicional.
        drupal_set_message(t('Error al crear la tarea. Detalles del error: @error_message', array('@error_message' => $error_message)), 'error');
    } else {
        // Redirigir al usuario a la página de listado de tareas.
        drupal_set_message(t('La tarea ha sido creada satisfactoriamente.'));
        $form_state['redirect'] = 'tasks/list';
    }
}