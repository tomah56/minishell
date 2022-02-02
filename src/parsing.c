/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:20:45 by sreinhol          #+#    #+#             */
/*   Updated: 2022/02/02 23:07:30 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// error cases:
// pipe and nothing after it
// two metacharacters after each other
// after heredoc next token has to be of type word
//
// save specific exit code in g_exit -> invalid syntax = 258
//
// saves redirections in struct and 
// removes redirection operators from argument list
// -> here we first check if there are pipes and then we check for redirections
// then we check every command on its own
// heredoc has to be performed always first even when not written first
// we read from left to right to define in and outfile
