char	**add_val_env(char *built_in)
{
	char **tab;
	char *egal;

	egal = ft_strrchr(built_in, '=');
	//printf("égal == %s\n", egal);
	tab = (char **) malloc (sizeof(char*) * (2 + 1));
	tab[0] = (char *) malloc (sizeof(char) * (ft_strlen(built_in) - (ft_strlen(egal)) + 1));
	tab[0] = ft_strncpy(tab[0], built_in, (ft_strlen(built_in) - (ft_strlen(egal))));
	tab[0][(ft_strlen(built_in) - (ft_strlen(egal)))] = '\0';
	tab[1] = (char *) malloc (sizeof(char) * ((ft_strlen(egal) + 1)));
	tab[1] = ft_strcpy(tab[1], egal + 1);
	tab[1][ft_strlen(egal) + 1] = '\0';
	return (tab);
}