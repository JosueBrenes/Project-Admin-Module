<?php

// Callback para la página de listado de proyectos.
function project_manager_projects_page() {
    // Verificar permiso de ver proyectos asignados para usuarios normales.
    if (!user_access('view own projects')) {
        return t('Acceso denegado. Debe tener permiso para ver sus propios proyectos.');
    }

    // Inicializar la variable de salida.
    $output = '';

    // Agregar botón para agregar un nuevo proyecto.
    $add_project_button = l(t('Add Project'), 'projects/add', array('attributes' => array('class' => array('button'), 'style' => 'margin-bottom: 3rem;')));
    $add_button_markup = '<div class="add-project-button">' . $add_project_button . '</div>';
    $output .= $add_button_markup;

    // Agregar CSS específico del módulo.
    drupal_add_css(drupal_get_path('module', 'project_manager') . '/css/styles.css');

    // Obtener los nodos de tipo "project".
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'project')
        ->propertyCondition('status', NODE_PUBLISHED) // Filtrar solo los nodos publicados
        ->propertyOrderBy('created', 'DESC'); // Ordenar por fecha de creación descendente.
    $result = $query->execute();

    // Verificar si se encontraron nodos de proyectos publicados.
    if (isset($result['node'])) {
        // Construir la tabla HTML para mostrar los proyectos.
        $rows = array();
        foreach ($result['node'] as $node) {
            $node = node_load($node->nid); // Cargar el nodo completo.

            // Obtener otros detalles del proyecto.
            $state = isset($node->field_status['und'][0]['value']) ? check_plain($node->field_status['und'][0]['value']) : '-';
            $client = isset($node->field_client['und'][0]['value']) ? check_plain($node->field_client['und'][0]['value']) : '-';
            $priority_value = isset($node->field_priority['und'][0]['value']) ? $node->field_priority['und'][0]['value'] : '';
            $start_date = isset($node->field_project_start_date['und'][0]['value']) ? format_date($node->field_project_start_date['und'][0]['value'], 'custom', 'Y-m-d') : '-';
            $end_date = isset($node->field_project_end_date['und'][0]['value']) ? format_date($node->field_project_end_date['und'][0]['value'], 'custom', 'Y-m-d') : '-';

            // Convertir el valor de prioridad de número a texto.
            $priorities = array(
                3 => 'High',
                2 => 'Medium',
                1 => 'Low',
            );
            $priority = isset($priorities[$priority_value]) ? check_plain($priorities[$priority_value]) : '-';

            // Obtener la descripción del proyecto.
            $description = isset($node->field_project_description['und'][0]['value']) ? check_plain($node->field_project_description['und'][0]['value']) : '-';

            $row = array(
                $node->nid,
                check_plain($node->title),
                $description,
                $state,
                $start_date,
                $end_date,
                $client,
                $priority,
                l(t('Edit'), 'projects/edit/' . $node->nid),
                l(t('Delete'), 'delete/' . $node->nid),
            );

            $rows[] = $row;
        }

        $header = array(
            'ID',
            'Project Name',
            'Description',
            'Status',
            'Start Date',
            'End Date',
            'Client',
            'Priority',
            'Actions',
            'Delete',
        );

        // Genera la tabla HTML.
        $output .= theme('table', array('header' => $header, 'rows' => $rows));
    } else {
        $output .= t('No projects found.');
    }
    return $output;
}

/**
 * Función de envío del formulario para agregar proyectos.
 */
function project_manager_project_add_form_submit($form, &$form_state) {
    global $user;

    // Crear un nuevo nodo de tipo "project".
    $node = new stdClass();
    $node->type = 'project'; // Tipo de nodo definido en tu instalación de Drupal.
    $node->uid = $user->uid;
    $node->status = 1; // Publicar el nodo automáticamente.
    node_object_prepare($node);

    // Asignar valores de los campos del formulario al nodo.
    $node->title = $form_state['values']['title'];
    $node->language = LANGUAGE_NONE;
    $node->field_project_description[$node->language][0]['value'] = $form_state['values']['field_project_description'];
    $node->field_project_start_date['und'][0]['value'] = strtotime($form_state['values']['start_date']);
    $node->field_project_end_date['und'][0]['value'] = strtotime($form_state['values']['end_date']);
    $node->field_participants['und'][0]['value'] = $form_state['values']['participants'];
    $node->field_status['und'][0]['value'] = $form_state['values']['status'];
    $node->field_client['und'][0]['value'] = $form_state['values']['client'];
    $node->field_task_email['und'][0]['value'] = $form_state['values']['field_task_email']; // Agregar email aquí

    // Guardar el archivo adjunto.
    $file = file_save_upload('file_upload', array(
        'file_validate_extensions' => array('pdf'), // Permitir solo archivos PDF.
    ));

    if ($file) {
        // Mover el archivo cargado a la carpeta pública.
        $public_path = 'public://files_projects/';
        if (file_prepare_directory($public_path, FILE_CREATE_DIRECTORY)) {
            file_move($file, $public_path . $file->filename, FILE_EXISTS_REPLACE);
        }
    }

    // Convertir el valor de prioridad seleccionado de texto a número.
    $priorities = array(
        'Alta' => 3,
        'Media' => 2,
        'Baja' => 1,
    );
    $node->field_priority['und'][0]['value'] = $priorities[$form_state['values']['priority']];

    // Guardar el nodo.
    node_save($node);

    // Redirigir al usuario a la página de visualización del proyecto recién creado.
    drupal_set_message(t('El proyecto ha sido creado satisfactoriamente.'));
    $form_state['redirect'] = 'projects/list'; // Página de listado de proyectos.
}

/**
 * Formulario para agregar un nuevo proyecto.
 */
function project_manager_project_add_form($form, &$form_state, $node = NULL) {
    // Campo de título del proyecto.
    $form['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Project Name'),
        '#required' => TRUE,
    );

    $form['field_project_description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#required' => TRUE,
    );

    // Campo de fecha de inicio del proyecto.
    $form['start_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('Start Date'),
        '#date_format' => 'Y-m-d',
        '#required' => TRUE,
    );

    // Campo de fecha de finalización del proyecto.
    $form['end_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('End Date'),
        '#date_format' => 'Y-m-d',
        '#required' => TRUE,
    );

    // Campo de participantes del proyecto.
    $form['participants'] = array(
        '#type' => 'textfield',
        '#title' => t('Participants'),
        '#required' => TRUE,
    );

    $form['field_task_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#required' => TRUE,
        '#element_validate' => array('email_field_validate'),
        '#field_name' => 'field_task_email',
    );

    // Campo de estado del proyecto.
    $form['status'] = array(
        '#type' => 'select',
        '#title' => t('Estado'),
        '#options' => array(
            'En Progreso' => t('In Progress'),
            'Completado' => t('Completed'),
            'Pendiente' => t('Pending'),
        ),
        '#required' => TRUE,
    );

    // Campo de cliente del proyecto.
    $form['client'] = array(
        '#type' => 'textfield',
        '#title' => t('Client'),
        '#required' => TRUE,
    );

    // Campo de prioridad del proyecto.
    $form['priority'] = array(
        '#type' => 'select',
        '#title' => t('Prioridad'),
        '#options' => array(
            'Alta' => t('High'),
            'Media' => t('Medium'),
            'Baja' => t('Low'),
        ),
        '#required' => TRUE,
    );

    // Campo de carga de archivo adjunto.
    $form['file_upload'] = array(
        '#type' => 'file',
        '#title' => t('Attach File (PDF)'),
    );

    // Botón de envío del formulario.
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Add Project'),
    );

    return $form;
} 
    // Función de validación de correo electrónico personalizada
    function email_field_validate($element, &$form_state) {
        $value = $form_state['values'][$element['#field_name']];
        if (!valid_email_address($value)) {
            form_error($element, t('Please enter a valid email address.'));
        }
    }

/**
 * Formulario para editar un proyecto existente.
 */
function project_manager_project_edit_form($form, &$form_state, $node) {
    // Cargar el nodo del proyecto.
    $node = node_load($node->nid);

    // Campo de título del proyecto.
    $form['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Project Name'),
        '#required' => TRUE,
        '#default_value' => $node->title,
    );

    $form['field_project_description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#required' => TRUE,
        '#default_value' => isset($node->field_project_description[$node->language][0]['value']) ? $node->field_project_description[$node->language][0]['value'] : '',
    );

    // Campo de fecha de inicio del proyecto.
    $form['start_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('Start Date'),
        '#date_format' => 'Y-m-d',
        '#required' => TRUE,
        '#default_value' => isset($node->field_project_start_date['und'][0]['value']) ? date('Y-m-d', $node->field_project_start_date['und'][0]['value']) : '',
    );

    // Campo de fecha de finalización del proyecto.
    $form['end_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('End Date'),
        '#date_format' => 'Y-m-d',
        '#required' => TRUE,
        '#default_value' => isset($node->field_project_end_date['und'][0]['value']) ? date('Y-m-d', $node->field_project_end_date['und'][0]['value']) : '',
    );

    // Campo de participantes del proyecto.
    $form['participants'] = array(
        '#type' => 'textfield',
        '#title' => t('Participants'),
        '#required' => TRUE,
        '#default_value' => isset($node->field_participants['und'][0]['value']) ? $node->field_participants['und'][0]['value'] : '',
    );      

    $form['field_task_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#required' => TRUE,
        '#default_value' => isset($node->field_task_email['und'][0]['value']) ? $node->field_task_email['und'][0]['value'] : '',
        '#element_validate' => array('email_field_validate'), 
        '#field_name' => 'field_task_email',
    );      

    // Campo de estado del proyecto.
    $form['status'] = array(
        '#type' => 'select',
        '#title' => t('Estado'),
        '#options' => array(
            'En Progreso' => t('In Progress'),
            'Completado' => t('Completed'),
            'Pendiente' => t('Pending'),
        ),
        '#required' => TRUE,
        '#default_value' => isset($node->field_status['und'][0]['value']) ? $node->field_status['und'][0]['value'] : '',
    );

    // Campo de cliente del proyecto.
    $form['client'] = array(
        '#type' => 'textfield',
        '#title' => t('Client'),
        '#required' => TRUE,
        '#default_value' => isset($node->field_client['und'][0]['value']) ? $node->field_client['und'][0]['value'] : '',
    );

    // Campo de prioridad del proyecto.
    $form['priority'] = array(
        '#type' => 'select',
        '#title' => t('Priority'),
        '#options' => array(
            'Alta' => t('High'),
            'Media' => t('Medium'),
            'Baja' => t('Low'),
        ),
        '#required' => TRUE,
        '#default_value' => isset($node->field_priority['und'][0]['value']) ? $node->field_priority['und'][0]['value'] : '',
    );

    // Campo para cargar el archivo adjunto.
    $form['file_upload'] = array(
        '#type' => 'managed_file',
        '#title' => t('Attach File (PDF)'),
        '#description' => t('Attach a PDF file related to the project.'),
        '#upload_validators' => array(
            'file_validate_extensions' => array('pdf'),
        ),
    );

    // Botón de enviar.
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Changes'),
    );

    // Ocultar el campo de ID del nodo.
    $form['nid'] = array(
        '#type' => 'value',
        '#value' => $node->nid,
    );

    return $form;
}

/**
 * Función de envío del formulario para editar un proyecto.
 */
function project_manager_project_edit_form_submit($form, &$form_state) {
    // Obtener el ID del nodo del proyecto.
    $node_id = $form_state['values']['nid'];

    // Cargar el nodo del proyecto.
    $node = node_load($node_id);

    // Actualizar los valores del nodo con los valores del formulario.
    $node->title = $form_state['values']['title'];
    $node->body[$node->language][0]['value'] = $form_state['values']['field_project_description']; // Corrección aquí

    // Otros campos del formulario.
    $node->field_project_start_date['und'][0]['value'] = strtotime($form_state['values']['start_date']);
    $node->field_project_end_date['und'][0]['value'] = strtotime($form_state['values']['end_date']);
    $node->field_participants['und'][0]['value'] = $form_state['values']['participants'];
    $node->field_status['und'][0]['value'] = $form_state['values']['status'];
    $node->field_client['und'][0]['value'] = $form_state['values']['client'];
    $node->field_task_email['und'][0]['value'] = $form_state['values']['field_task_email']; // Agregar email aquí

    // Guardar el archivo adjunto.
    $file = file_save_upload('file_upload', array(
        'file_validate_extensions' => array('pdf'), // Permitir solo archivos PDF.
    ));

    if ($file) {
        // Mover el archivo cargado a la carpeta designada.
        $file_path = file_default_scheme() . '://files_projects/' . $file->filename;
        if (file_move($file, $file_path)) {
            // Guardar la ubicación del archivo en el nodo.
            $node->archivo_proyecto[LANGUAGE_NONE][0] = (array)$file;
            // Guardar la URL del archivo en un campo adicional.
            $node->archivo_url[LANGUAGE_NONE][0]['value'] = file_create_url($file->uri);
        }
    }

    // Convertir el valor de prioridad seleccionado de texto a número.
    $priorities = array(
        'Alta' => 3,
        'Media' => 2,
        'Baja' => 1,
    );
    $node->field_priority['und'][0]['value'] = $priorities[$form_state['values']['priority']];

    // Guardar el nodo.
    node_save($node);

    // Redirigir al usuario a la página de listado de proyectos.
    drupal_set_message(t('El proyecto ha sido actualizado satisfactoriamente.'));
    $form_state['redirect'] = 'projects/list';
}

