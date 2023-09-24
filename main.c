#include"ProjetFinSas.h"
int main() {
    arbreB a = NULL;
    int choice;
    int task_id;
    int search_option;
    char search_title[20];

    do {
        printf("\n=== Task Management System ===\n");
        printf("1. Ajouter plusieur taches\n");
        printf("2. Afficher les Taches\n");
        printf("3. Afficher les Taches dont le deadline est dans 3 jours ou moins\n");
        printf("4. Trier les Taches par deadline\n");
        printf("5. Trier les taches par titre\n");
        printf("6. Supprimer une tache\n");
        printf("7. Modifier une tache\n");
        printf("8. Afficher les Statistiques de touts les Taches\n");
        printf("9.Rechercher par Id et par Titre\n");
        printf("10.Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add tasks
                printf("\ntu peut choisir combien de tache que vous avez ajouter : ");
                int t;
                scanf("%d",&t);
                a = ajoutPlusieurTaches(a, t);
                break;

            case 2:
                // Display tasks
                afficherArbre(a);
                break;

            case 3:
                // Display tasks under 3 days
                afficher_moin_3day(a);
                break;

            case 4:
                // Sort tasks by deadline
                trieParDeadline(a);
                break;

            case 5:
                // Sort tasks by title
                trieParTitre(a);
                break;

            case 6:
                // Remove a task
                printf("Enter the ID of the task to remove: ");
                scanf("%d", &task_id);
                a = supprimerElt(task_id, a);
                break;

            case 7:
        // Modify a task
		        printf("Enter the ID of the task to modify: ");
		        scanf("%d", &task_id);
		
		        int modify_choice;
		        printf("\n=== Modification Options ===\n");
		        printf("1. Modify task status\n");
		        printf("2. Modify task deadline\n");
		        printf("3. Modify task description\n");
		        printf("Enter your choice: ");
		        scanf("%d", &modify_choice);
		
		        switch (modify_choice) {
		            case 1:
		                // Modify task status
		                modifierStat(a, task_id);
		                break;
		
		            case 2:
		                // Modify task deadline
		                modifierTacheDeadline(a, task_id);
		                break;
		
		            case 3:
		                // Modify task description
		                modifierTacheDes(a, task_id);
		                break;
		
		            default:
		                printf("Invalid modification choice. Please try again.\n");
		                break;
		        }
		        break;
            case 8:
			
			    printf("=== Task Statistics ===\n");
			    printf("Number of incomplete tasks: %d\n", nombreTacheIncomplet(a));
			    printf("Number of complete tasks: %d\n", nombreTacheComplet(a));
			    printf("Days until deadline for each task:\n");
			    nombreJourJusqDelai(a);
			    break;
			
			case 9:
			    printf("Search by:\n");
			    printf("1. ID\n");
			    printf("2. Title\n");
			    printf("Enter your choice: ");
			    scanf("%d", &search_option);
			
			    switch (search_option) {
			        case 1:
			            printf("Enter the ID to search for: ");
			            scanf("%d", &task_id);
			            rechercherId(a, task_id);
			            break;
			
			        case 2:
			            printf("Enter the title to search for: ");
			            scanf("%s", search_title);
			            rechercherTit(a, search_title);
			            break;
			
			        default:
			            printf("Invalid search option. Please try again.\n");
			            break;
			    }
			    break;
			case 10:
			    // Exit
			    printf("Exiting program.\n");
			    break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 10);

    return 0;
}


