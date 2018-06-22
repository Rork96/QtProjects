UPDATE public.admin_groups SET "Group name" = 'Agent', "Group description" = 'Agent goup' WHERE key = 1;
UPDATE public.admin_groups SET "Group name" = 'Tester', "Group description" = 'Tester group' WHERE key = 5;
UPDATE public.admin_groups SET "Group name" = 'Advertising', "Group description" = 'Advertising group' WHERE key = 7;
UPDATE public.admin_groups SET "Group name" = 'Owner', "Group description" = 'Owner group' WHERE key = 2;
UPDATE public.admin_groups SET "Group name" = 'Guest', "Group description" = 'Guest group' WHERE key = 8;
UPDATE public.users SET username = 'Admin', password = 'admin';
UPDATE public.users SET username = 'user', password = '123';