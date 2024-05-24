<?php

function project_delete($node_id) {

    // Load the node corresponding to the content ID.
    $node = node_load($node_id);

    if ($node) {
        // Change the node status to 0 to "delete" it.
        $node->status = 0;
        node_save($node);

        // Get the content type.
        $content_type = $node->type;

        // Define the message and redirection based on content type.
        switch ($content_type) {
            case 'task':
                $message = t('The task has been deleted.');
                $redirect = 'tasks';
                break;
            case 'project':
                $message = t('The project has been deleted.');
                $redirect = 'projects/list';
                break;
            default:
                $message = t('The content has been deleted.');
                $redirect = '';
                break;
        }

        // Set up the message.
        drupal_set_message($message);

        // Redirect the user to the corresponding destination.
        if (!empty($redirect)) {
            drupal_goto($redirect);
        }
    } else {
        drupal_set_message(t('The content could not be loaded for deletion.'), 'error');
    }
}

function task_delete($nid) {

    $nid = arg(2);

    $node = node_load($nid);

    if ($node) {

        $node->status = 0;
        node_save($node);

        drupal_set_message(t('The task has been deleted.'));

        drupal_goto('tasks/list');
    } else {
        drupal_set_message(t('The task could not be loaded for deletion.'), 'error');
    }
}
