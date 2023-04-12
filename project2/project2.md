***
## Exercise 1
$$\begin{aligned}
\mathbb{E}[X] &= \Vert f \Vert _{2}^{2} + \mathbb{E}[\sum_{(j,k) \in [n]\times [n]: j \neq k} 1_{[h(j) = h(k)]} g(j) g(k) f_j f_k] \\
&\Downarrow (1)\\
&= \Vert f \Vert _{2}^{2} + \sum_{(j,k) \in [n]\times [n]: j \neq k} \mathbb{E}[1_{[h(j) = h(k)]} g(j) g(k) f_j f_k] \\
&\Downarrow (2)\\
&= \Vert f \Vert _{2}^{2} + \sum_{(j,k) \in [n]\times [n]: j \neq k} \mathbb{E}[1_{[h(j) = h(k)]}] \mathbb{E}[g(j) g(k)] f_j f_k \\
&\Downarrow (3)\\
&= \Vert f \Vert _{2}^{2} + \sum_{(j,k) \in [n]\times [n]: j \neq k} \mathbb{E}[1_{[h(j) = h(k)]}] \mathbb{E}[g(j)] \mathbb{E}[g(k)] f_j f_k \\
&\Downarrow (4)\\
&= \Vert f \Vert _{2}^{2}
\end{aligned}$$
\**The derivation (1) uses the **linearity of expectation**.*
\**The derivation (2) uses the independence of $h$ and $g$.*
\**The derivation (3) uses the independence of the hash values of distinct keys.*
\**The derivation (4) is because $\mathbb{E}[g(j)]=0$.*
***
## Exercise 2
$$\begin{aligned}
Var(X) &= Var(\Vert f \Vert _{2}^{2} + \sum_{(j,k) \in [n]\times [n]: j \neq k} 1_{[h(j) = h(k)]} g(j) g(k) f_j f_k]) \\
&= Var(\sum_{(j,k) \in [n]\times [n]: j \neq k} 1_{[h(j) = h(k)]} g(j) g(k) f_j f_k]) \\
&= \mathbb{E}[(\sum_{(j,k) \in [n]\times [n]: j \neq k} 1_{[h(j) = h(k)]} g(j) g(k) f_j f_k])^2] -\\ &\ \ \ \ \ \mathbb{E}^2[\sum_{(j,k) \in [n]\times [n]: j \neq k} 1_{[h(j) = h(k)]} g(j) g(k) f_j f_k]] \\
&= \mathbb{E}[(\sum_{(j,k) \in [n]\times [n]: j \neq k} 1_{[h(j) = h(k)]} g(j) g(k) f_j f_k])^2]\\
&= \mathbb{E}[\sum_{\substack{(j,k) \in [n]\times [n]: j \neq k\\ (p,q) \in [n]\times [n]: p \neq q}}1_{[h(j) = h(k)]} 1_{[h(p) = h(q)]} g(j) g(k) g(p) g(q)f_j f_k f_p f_q] \\
&= \sum_{\substack{(j,k) \in [n]\times [n]: j \neq k\\ (p,q) \in [n]\times [n]: p \neq q}} \mathbb{E}[1_{[h(j) = h(k)]} 1_{[h(p) = h(q)]} g(j) g(k) g(p) g(q)f_j f_k f_p f_q] \\
&\overset{(1)}{=} \sum_{\substack{(j,k) \in [n]\times [n]: j \neq k\\ (p,q) \in [n]\times [n]: p \neq q \\p=j, q=k}} \mathbb{E}[1_{[h(j) = h(k)]} 1_{[h(p) = h(q)]} g(j) g(k) g(p) g(q)f_j f_k f_p f_q] +\\ &\ \ \ \ \ 
\sum_{\substack{(j,k) \in [n]\times [n]: j \neq k\\ (p,q) \in [n]\times [n]: p \neq q \\p=k, q=j}} \mathbb{E}[1_{[h(j) = h(k)]} 1_{[h(p) = h(q)]} g(j) g(k) g(p) g(q)f_j f_k f_p f_q] +\\ &\ \ \ \ \ 
\sum_{\substack{(j,k) \in [n]\times [n]: j \neq k\\ (p,q) \in [n]\times [n]: p \neq q \\p,q\notin \{j,k\}}} \mathbb{E}[1_{[h(j) = h(k)]} 1_{[h(p) = h(q)]} g(j) g(k) g(p) g(q)f_j f_k f_p f_q] \\
&\overset{(2)}{=} 2\sum_{(j,k) \in [n]\times [n]: j \neq k} \mathbb{E}[1^2_{[h(j) = h(k)]}] \mathbb{E}[g^2(j)] \mathbb{E}[g^2(k)] f_j^2 f_k^2\\
&\overset{(3)}{=} 2\sum_{(j,k) \in [n]\times [n]: j \neq k} \mathbb{E}[1_{[h(j) = h(k)]}] f_j^2 f_k^2\\
&= 2\sum_{(j,k) \in [n]\times [n]: j \neq k} Pr[h(j) = h(k)] f_j^2 f_k^2\\
&= \frac{2}{r}\sum_{(j,k) \in [n]\times [n]: j \neq k}f_j^2 f_k^2\\
&\leq \frac{2}{r} (\sum_{j \in [n]\times [n]}f_j^2)^2 \\
&= \frac{2(\Vert f \Vert _{2}^{2})^2}{r}
\end{aligned}$$
The key derivations are equal signs (1), (2) and (3).
\* *For (1), we partition the summation into 3 different parts: $p=j$ & $q=k$, $p=k$ & $q=j$ and $p,q \notin \{i,j\}$. The last part can be written as $\sum_{\substack{(j,k) \in [n]\times [n]: j \neq k\\ (p,q) \in [n]\times [n]: p \neq q \\p,q\notin \{j,k\}}} \mathbb{E}[1_{[h(j) = h(k)]}1_{[h(p) = h(q)]}] \mathbb{E}[g(j)] \mathbb{E}[g(k)] \mathbb{E}[g(p)] \mathbb{E}[g(q)]f_j f_k f_p f_q$ because $h$ and $g$ are independent and $g$ is 4-wise independent. Again this term is obviously 0 due to $\mathbb{E}[g(j)] = 0$.*
\* *For (2), the first 2 parts above are actually the same, so they can be merged.*
\* *For (3), this holds because $\mathbb{E}[g^2(j)] = 1$.*
***
## Exercise 3
According to the Chebyshev’s Inequality, we have $Pr[|X - \mathbb{E}[X]| > k] < \frac{Var(X)}{k^2}$. Based on the derivations above, the inequality becomes
$$
Pr[|X - \Vert f \Vert _{2}^{2}| > \varepsilon \Vert f \Vert _{2}^{2}] < \frac{Var(X)}{\varepsilon^2 (\Vert f \Vert _{2}^{2})^2} \leq \frac{2(\Vert f \Vert _{2}^{2})^2}{r\varepsilon^2(\Vert f \Vert _{2}^{2})^2} = \frac{2}{r\varepsilon^2} < \frac{1}{4}
$$
We want to bound the probability to be a quarter at most, then
$$
r > \frac{8}{\varepsilon^2}
$$
***
